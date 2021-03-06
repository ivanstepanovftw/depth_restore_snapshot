// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
// https://www.notion.so/7def976a576c4e329d9e99c8395246e0
/**
 * @author Ivan Stepanov <ivanstepanovftw@gmail.com>
 */

#include <iostream>
#include <regex>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <array>
#include <iomanip>
#include <map>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"


#if defined(__GNUC__)
#  define LIKELY(x)     (__builtin_expect(!!(x), 1))
#  define UNLIKELY(x)   (__builtin_expect(!!(x), 0))
#else
#  define LIKELY(x)     (x)
#  define UNLIKELY(x)   (x)
#endif

namespace {
  std::string logs = R"raw([2020-08-20 13:28:46.489] [exchange_tools] [debug] [HuobiDMHandlerDepthMessage] current time: 1597930123294697, message: {"ch":"market.BTC_CW.depth.size_20.high_freq","tick":{"asks":[[11785.6,132],[11785.69,133],[11785.86,133],[11786,133],[11786.44,20],[11786.58,133],[11786.83,25],[11786.91,133],[11787,58],[11788.05,147],[11788.15,35],[11788.95,892],[11789.04,27],[11789.52,27],[11789.53,400],[11789.65,2],[11789.75,217],[11789.86,87],[11790,3],[11790.05,10]],"bids":[[11785.59,236],[11784.64,778],[11784.52,38],[11784.17,822],[11783.32,672],[11783.31,27],[11782.32,10],[11781.52,147],[11781.37,3],[11781.08,3],[11780.59,28],[11780.55,100],[11780.42,297],[11779.73,10],[11779.44,2],[11779.39,23],[11779.29,10],[11779.22,10],[11779.2,27],[11778.91,25]],"ch":"market.BTC_CW.depth.size_20.high_freq","event":"snapshot","id":94213098920,"mrid":94213098920,"ts":1597930123130,"version":225462219},"ts":1597930123131}
  [2020-08-20 13:28:46.489] [exchange_tools] [debug] [HuobiDMHandlerDepthMessage] current time: 1597930123367903, message: {"ch":"market.BTC_CW.depth.size_20.high_freq","tick":{"asks":[],"bids":[[11785.59,290]],"ch":"market.BTC_CW.depth.size_20.high_freq","event":"update","id":94213099139,"mrid":94213099139,"ts":1597930123220,"version":225462220},"ts":1597930123221}
  [2020-08-20 13:28:46.489] [exchange_tools] [debug] [HuobiDMHandlerDepthMessage] current time: 1597930123390473, message: {"ch":"market.BTC_CW.depth.size_20.high_freq","tick":{"asks":[[11789.52,120]],"bids":[],"ch":"market.BTC_CW.depth.size_20.high_freq","event":"update","id":94213099188,"mrid":94213099188,"ts":1597930123243,"version":225462221},"ts":1597930123243}
  [2020-08-20 13:28:46.489] [exchange_tools] [debug] [HuobiDMHandlerDepthMessage] current time: 1597930123461062, message: {"ch":"market.BTC_CW.depth.size_20.high_freq","tick":{"asks":[],"bids":[[11785.59,288]],"ch":"market.BTC_CW.depth.size_20.high_freq","event":"update","id":94213099451,"mrid":94213099451,"ts":1597930123312,"version":225462222},"ts":1597930123312}
  [2020-08-20 13:28:46.489] [exchange_tools] [debug] [HuobiDMHandlerDepthMessage] current time: 1597930123540570, message: {"ch":"market.BTC_CW.depth.size_20.high_freq","tick":{"asks":[[11789.52,27]],"bids":[],"ch":"market.BTC_CW.depth.size_20.high_freq","event":"update","id":94213099758,"mrid":94213099758,"ts":1597930123393,"version":225462223},"ts":1597930123393}
  [2020-08-20 13:28:46.489] [exchange_tools] [debug] [HuobiDMHandlerDepthMessage] current time: 1597930123577811, message: {"ch":"market.BTC_CW.depth.size_20.high_freq","tick":{"asks":[[11785.6,129]],"bids":[],"ch":"market.BTC_CW.depth.size_20.high_freq","event":"update","id":94213099839,"mrid":94213099839,"ts":1597930123430,"version":225462224},"ts":1597930123431}
  [2020-08-20 13:28:46.489] [exchange_tools] [debug] [HuobiDMHandlerDepthMessage] current time: 1597930123662683, message: {"ch":"market.BTC_CW.depth.size_20.high_freq","tick":{"asks":[[11785.6,132]],"bids":[],"ch":"market.BTC_CW.depth.size_20.high_freq","event":"update","id":94213100079,"mrid":94213100079,"ts":1597930123513,"version":225462225},"ts":1597930123513}
  [2020-08-20 13:28:46.489] [exchange_tools] [debug] [HuobiDMHandlerDepthMessage] current time: 1597930123900472, message: {"ch":"market.BTC_CW.depth.size_20.high_freq","tick":{"asks":[[11785.6,129]],"bids":[],"ch":"market.BTC_CW.depth.size_20.high_freq","event":"update","id":94213100923,"mrid":94213100923,"ts":1597930123753,"version":225462226},"ts":1597930123753}
  [2020-08-20 13:28:46.489] [exchange_tools] [debug] [HuobiDMHandlerDepthMessage] current time: 1597930123995626, message: {"ch":"market.BTC_CW.depth.size_20.high_freq","tick":{"asks":[[11785.6,132]],"bids":[],"ch":"market.BTC_CW.depth.size_20.high_freq","event":"update","id":94213101198,"mrid":94213101198,"ts":1597930123843,"version":225462227},"ts":1597930123843}
  [2020-08-20 13:28:46.489] [exchange_tools] [debug] [HuobiDMHandlerDepthMessage] current time: 1597930124238573, message: {"ch":"market.BTC_CW.depth.size_20.high_freq","tick":{"asks":[[11785.6,129]],"bids":[],"ch":"market.BTC_CW.depth.size_20.high_freq","event":"update","id":94213101876,"mrid":94213101876,"ts":1597930124090,"version":225462228},"ts":1597930124091}
  [2020-08-20 13:28:46.489] [exchange_tools] [debug] [HuobiDMHandlerDepthMessage] current time: 1597930124334868, message: {"ch":"market.BTC_CW.depth.size_20.high_freq","tick":{"asks":[[11785.6,132]],"bids":[[11785.59,234],[11783.32,0],[11778.89,5]],"ch":"market.BTC_CW.depth.size_20.high_freq","event":"update","id":94213102170,"mrid":94213102170,"ts":1597930124182,"version":225462229},"ts":1597930124182}
  [2020-08-20 13:28:46.489] [exchange_tools] [debug] [HuobiDMHandlerDepthMessage] current time: 1597930124365699, message: {"ch":"market.BTC_CW.depth.size_20.high_freq","tick":{"asks":[],"bids":[[11782.33,672],[11778.89,0]],"ch":"market.BTC_CW.depth.size_20.high_freq","event":"update","id":94213102236,"mrid":94213102236,"ts":1597930124210,"version":225462230},"ts":1597930124211}
  [2020-08-20 13:28:46.489] [exchange_tools] [debug] [HuobiDMHandlerDepthMessage] current time: 1597930124411823, message: {"ch":"market.BTC_CW.depth.size_20.high_freq","tick":{"asks":[[11789.53,493]],"bids":[],"ch":"market.BTC_CW.depth.size_20.high_freq","event":"update","id":94213102367,"mrid":94213102367,"ts":1597930124263,"version":225462231},"ts":1597930124263}
  [2020-08-20 13:28:46.489] [exchange_tools] [debug] [HuobiDMHandlerDepthMessage] current time: 1597930124483495, message: {"ch":"market.BTC_CW.depth.size_20.high_freq","tick":{"asks":[[11789.53,400]],"bids":[],"ch":"market.BTC_CW.depth.size_20.high_freq","event":"update","id":94213102629,"mrid":94213102629,"ts":1597930124332,"version":225462232},"ts":1597930124332}
  [2020-08-20 13:28:46.489] [exchange_tools] [debug] [HuobiDMHandlerDepthMessage] current time: 1597930124653843, message: {"ch":"market.BTC_CW.depth.size_20.high_freq","tick":{"asks":[[11789.52,121]],"bids":[],"ch":"market.BTC_CW.depth.size_20.high_freq","event":"update","id":94213103187,"mrid":94213103187,"ts":1597930124504,"version":225462233},"ts":1597930124505}
  [2020-08-20 13:28:46.489] [exchange_tools] [debug] [HuobiDMHandlerDepthMessage] current time: 1597930124690135, message: {"ch":"market.BTC_CW.depth.size_20.high_freq","tick":{"asks":[[11785.6,129]],"bids":[],"ch":"market.BTC_CW.depth.size_20.high_freq","event":"update","id":94213103420,"mrid":94213103420,"ts":1597930124542,"version":225462234},"ts":1597930124542}
  [2020-08-20 13:28:46.489] [exchange_tools] [debug] [HuobiDMHandlerDepthMessage] current time: 1597930124812908, message: {"ch":"market.BTC_CW.depth.size_20.high_freq","tick":{"asks":[[11785.6,132]],"bids":[],"ch":"market.BTC_CW.depth.size_20.high_freq","event":"update","id":94213103834,"mrid":94213103834,"ts":1597930124663,"version":225462235},"ts":1597930124664}
  [2020-08-20 13:28:46.489] [exchange_tools] [debug] [HuobiDMHandlerDepthMessage] current time: 1597930125012092, message: {"ch":"market.BTC_CW.depth.size_20.high_freq","tick":{"asks":[[11785.6,772],[11789.6,674],[11790.05,0]],"bids":[],"ch":"market.BTC_CW.depth.size_20.high_freq","event":"update","id":94213104416,"mrid":94213104416,"ts":1597930124863,"version":225462236},"ts":1597930124863}
  [2020-08-20 13:28:46.489] [exchange_tools] [debug] [HuobiDMHandlerDepthMessage] current time: 1597930125073442, message: {"ch":"market.BTC_CW.depth.size_20.high_freq","tick":{"asks":[],"bids":[[11785.59,204]],"ch":"market.BTC_CW.depth.size_20.high_freq","event":"update","id":94213104509,"mrid":94213104509,"ts":1597930124923,"version":225462237},"ts":1597930124923}
  [2020-08-20 13:28:46.489] [exchange_tools] [debug] [HuobiDMHandlerDepthMessage] current time: 1597930125130497, message: {"ch":"market.BTC_CW.depth.size_20.high_freq","tick":{"asks":[[11785.6,764],[11789.52,27]],"bids":[[11785.59,154]],"ch":"market.BTC_CW.depth.size_20.high_freq","event":"update","id":94213104739,"mrid":94213104739,"ts":1597930124983,"version":225462238},"ts":1597930124983}
  )raw";

  class Timer {
   public:
    explicit Timer(std::string what = "Timer")
        : m_what(std::move(what)), m_tp(std::chrono::high_resolution_clock::now()) {}

    ~Timer() {
      std::clog << m_what << ": done in " << calculate() << " seconds" << std::endl;
    }

    [[nodiscard]]
    double calculate() const {
      return std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - m_tp)
          .count();
    }

   private:
    std::string m_what;
    std::chrono::high_resolution_clock::time_point m_tp;
  };
}



class DepthSnapshot {
 protected:
  using stored_price_t = int64_t;
  using stored_amount_t = int64_t;

  int m_error_code = 0;
  double m_tick_size = 0.01; // To avoid epsilon, price will be divided by tick_size and stored as "key" in std::map.
  uint64_t m_timestamp = 0;
  // std::map is collection of key-value pairs, sorted by keys, keys are unique.
  // Implementation note: do not try to use another comparator, than {@code std::less}.
  // Price can be negative. To avoid integer overflow, signed integer used both for price and amount.
  std::map<stored_price_t, stored_amount_t> m_bids; // Buy orders. Last element is best price.
  std::map<stored_price_t, stored_amount_t> m_asks; // Sell orders. First element is best price.

  /**
   * Converts price
   */
  [[nodiscard]]
  inline stored_price_t storePrice(double price) const {
    return static_cast<stored_price_t>(price / m_tick_size);
  }

  [[nodiscard]]
  inline double restorePrice(stored_price_t key) const {
    return static_cast<double>(key) * m_tick_size;
  }

 public:
  DepthSnapshot() = default;

  /**
   * Returns tick size
   */
  [[nodiscard]]
  double getTickSize() const {
    return m_tick_size;
  }

  void setTickSize(double tickSize) {
    m_tick_size = tickSize;
  }

  /**
   * @returns {@code false} is something bad happen. Check {@code DepthSnapshot::error()}
   */
  bool apply(const std::string &message) {
    rapidjson::Document document;
    document.Parse(message.c_str());
    if UNLIKELY(!document.HasMember("tick")) {
      return true; // in case it is ping or invalid message
    }
    const auto &tick = document["tick"];
    const auto &ts = tick["ts"];
    m_timestamp = ts.GetUint64();

    if UNLIKELY(std::string_view(tick["event"].GetString()) == "snapshot") {
      m_bids.clear();
      m_asks.clear();
      for (const auto &bids : tick["bids"].GetArray()) {
        const auto &price_amount_pair = bids.GetArray();
        if UNLIKELY(price_amount_pair.Size() != 2) {
          m_error_code = 1;
          return false;
        }
        const auto &price_s = price_amount_pair.Begin();
        const auto &amount_s = price_s + 1;

        const stored_price_t price = storePrice(price_s->GetDouble());
        const stored_amount_t amount = amount_s->GetInt64();
        m_bids[price] = amount;
      }
      for (const auto &asks : tick["asks"].GetArray()) {
        const auto &price_amount_pair = asks.GetArray();
        if UNLIKELY(price_amount_pair.Size() != 2) {
          m_error_code = 1;
          return false;
        }
        const auto &price_s = price_amount_pair.Begin();
        const auto &amount_s = price_s + 1;

        const stored_price_t price = storePrice(price_s->GetDouble());
        const stored_amount_t amount = amount_s->GetInt64();
        m_asks[price] = amount;
      }
    }
    /**
     * Update event parsing
     */
    if LIKELY(std::string_view(tick["event"].GetString()) == "update") {
      for (const auto &bids : tick["bids"].GetArray()) {
        const auto &price_amount_pair = bids.GetArray();
        if UNLIKELY(price_amount_pair.Size() != 2) {
          m_error_code = 1;
          return false;
        }
        const auto &price_s = price_amount_pair.Begin();
        const auto &amount_s = price_s + 1;

        const stored_price_t price = storePrice(price_s->GetDouble());
        const stored_amount_t amount = amount_s->GetInt64();

        if (amount == 0) {
          m_bids.erase(price);
          continue;
        }
        m_bids[price] = amount;
        if (m_bids.size() > 20) {
          m_bids.erase(m_bids.begin());
        }
      }
      for (const auto &asks : tick["asks"].GetArray()) {
        const auto &price_amount_pair = asks.GetArray();
        if UNLIKELY(price_amount_pair.Size() != 2) {
          m_error_code = 1;
          return false;
        }
        const auto &price_s = price_amount_pair.Begin();
        const auto &amount_s = price_s + 1;

        const stored_price_t price = storePrice(price_s->GetDouble());
        const stored_amount_t amount = amount_s->GetInt64();

        if (amount == 0) {
          m_asks.erase(price);
          continue;
        }
        m_asks[price] = amount;
        if (m_asks.size() > 20) {
          m_asks.erase(prev(m_asks.end()));
        }
      }
    }
    // assert check
    if UNLIKELY(m_bids.size() > 20) {
      m_error_code = 2;
      return false;
    }
    if UNLIKELY(m_asks.size() > 20) {
      m_error_code = 2;
      return false;
    }
    return true;
  }

  [[nodiscard]]
  auto getTimestamp() const {
    return m_timestamp;
  }

  [[nodiscard]]
  auto getBestBid() const -> std::pair<double, int64_t> {
    if UNLIKELY(m_bids.empty())
      return {0., 0};
    const auto bestBid = prev(m_bids.end());
    return {restorePrice(bestBid->first), bestBid->second};
  }

  [[nodiscard]]
  auto getBestAsk() const -> std::pair<double, int64_t> {
    if UNLIKELY(m_asks.empty())
      return {0., 0};
    const auto bestAsk = m_asks.begin();
    return {restorePrice(bestAsk->first), bestAsk->second};
  }

  [[nodiscard]]
  std::string error() {
    std::string message;
    switch (m_error_code) {
      case 0: message = "No error"; break;
      case 1: message = "Pair [price,amount] is invalid"; break;
      case 2: message = "Bids or asks array size is > 20"; break;
    }
    m_error_code = 0;
    return message;
  }
};


int main() {
  using namespace rapidjson;
  Timer _main_timer("Overall");

  // Output file
  std::ofstream bestbidask("huobi_dm_depth.out.txt");
  bestbidask << std::setprecision(8);

  // Im using cache to measure real "message" parsing performance.
  // This vector contains "message"s from logs.
  std::vector<std::string> huobi_dm_depth_messages;
  const std::regex base_regex(R"regex(current time: (\d+), message: (.+))regex");

  std::ifstream huobi_dm_depth("huobi_dm_depth.log", std::ios::in);
  //std::istringstream huobi_dm_depth(logs);
  if (!huobi_dm_depth) {
    std::cerr << "Cannot open stream. Set working directory to path where 'huobi_dm_depth.log' is." << std::endl;
    return 1;
  }

  {
    Timer _timer("Parsing log file");
    std::string line;
    while (getline(huobi_dm_depth, line)) {
      std::smatch time_message_match;
      if (std::regex_search(line, time_message_match, base_regex)) {
        if (time_message_match.size() != 3) {
          std::clog << "Corrupted line? line: " << line << std::endl;
          for (auto &a : time_message_match) {
            std::clog << "Corrupted line? match: " << a << std::endl;
          }
          return 1;
        }

        //std::string current_time = time_message_match[1].str();
        std::string message = time_message_match[2].str();
        huobi_dm_depth_messages.emplace_back(message);
      }
    }
  }

  DepthSnapshot dom;
  {
    Timer _timer("Parsing " + std::to_string(huobi_dm_depth_messages.size()) + " messages");
    for (auto &message : huobi_dm_depth_messages) {
      bool success = dom.apply(message);
      if UNLIKELY(!success) {
        std::cerr << "Error: "<<dom.error()<<". Message: " << message << std::endl;
        return 1;
      }

      uint64_t ts = dom.getTimestamp();
      std::pair bid = dom.getBestBid();
      std::pair ask = dom.getBestAsk();
      bestbidask << ts << ", " << bid.first << ", " << bid.second << ", " << ask.first << ", " << ask.second << "\n";
    }
    std::cout << "Latency: " << (1e+3 * _timer.calculate() / static_cast<double>(huobi_dm_depth_messages.size()))
              << " ms per message"
              << std::endl;
  }

  return 0;
}
