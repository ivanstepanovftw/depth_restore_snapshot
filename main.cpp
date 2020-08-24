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
#include <algorithm>
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

    double calculate() {
      return std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - m_tp)
          .count();
    }

   private:
    std::string m_what;
    std::chrono::high_resolution_clock::time_point m_tp;
  };
}



class DepthSnapshot {
  rapidjson::Document d;

 protected:
  const static int64_t PRECISION_MULT = 400; // To avoid epsilon, multiply by this and convert to integer. Based on `1/<tick size>` formula.

  uint64_t m_timestamp{};
  // std::map is collection of key-value pairs, sorted by keys, keys are unique
  /// Note: do not try to use another comparator, than {@code std::less}.
  // Price can be negative. To avoid integer overflow, signed integer used both for price and amount
  std::map<int64_t /* (price * PRECISION_MULT) */, int64_t /* amount */> m_bids; // Buy orders. Last element (largest) is best price
  std::map<int64_t /* (price * PRECISION_MULT) */, int64_t /* amount */> m_asks; // Sell orders. First element (smallest) is best price

  inline static int64_t f2i(double f) {
    return static_cast<int64_t>(f * PRECISION_MULT);
  }

  inline static double i2f(int64_t i) {
    return static_cast<double>(i) / static_cast<double>(PRECISION_MULT);
  }

 public:
  DepthSnapshot() = default;

  [[maybe_unused]]
  explicit DepthSnapshot(const std::string &message) {
    apply(message);
  }

  /**
   * @returns {@code false} is something bad happen
   */
  bool apply(const std::string &message) {
    using namespace std;

    d.Parse(message.c_str());
    if UNLIKELY(!d.HasMember("tick")) {
      return true; // in case it is ping or invalid message
    }
    auto &tick = d["tick"];
    auto &ts = tick["ts"];
    m_timestamp = ts.GetUint64();

    if UNLIKELY(string_view(tick["event"].GetString()) == "snapshot") {
      m_bids.clear();
      m_asks.clear();
      for (const auto &bids : tick["bids"].GetArray()) {
        const auto kv = bids.GetArray();
        // todo check if size is eq to 2
        if UNLIKELY(kv.Empty())
          continue;
        const auto price = kv.Begin(); // float point
        const auto amount = price + 1; // integer

        const int64_t p = f2i(price->GetDouble());
        const int64_t v = amount->GetInt64();

        m_bids[p] = v;
      }
      for (const auto &bids : tick["asks"].GetArray()) {
        const auto kv = bids.GetArray();
        if UNLIKELY(kv.Empty())
          continue;
        const auto price = kv.Begin();
        const auto amount = price + 1;

        const int64_t p = f2i(price->GetDouble());
        const int64_t v = amount->GetInt64();

        m_asks[p] = v;
      }
    }
    /**
     * Update event parsing
     */
    if LIKELY(std::string_view(tick["event"].GetString()) == "update") {
      for (const auto &bids : tick["bids"].GetArray()) {
        const auto kv = bids.GetArray();
        if UNLIKELY(kv.Empty())
          continue;
        const auto price = kv.Begin();
        const auto amount = price + 1;

        const int64_t p = f2i(price->GetDouble());
        const int64_t v = amount->GetInt64();

        if UNLIKELY(v == 0) {
          m_bids.erase(p);
          continue;
        }
        m_bids[p] = v;
        if (m_bids.size() > 20) {
          m_bids.erase(m_bids.begin());
        }
      }
      for (const auto &asks : tick["asks"].GetArray()) {
        const auto kv = asks.GetArray();
        if UNLIKELY(kv.Empty())
          continue;
        const auto price = kv.Begin();
        const auto amount = price + 1;

        const int64_t p = f2i(price->GetDouble());
        const int64_t v = amount->GetInt64();

        if UNLIKELY(v == 0) {
          m_asks.erase(p);
          continue;
        }
        m_asks[p] = v;
        if (m_asks.size() > 20) {
          m_asks.erase(prev(m_asks.end()));
        }
      }
    }
    // assert check
    if UNLIKELY(m_bids.size() > 20) {
      cerr << "m_bids size > 20" << endl;
      return false;
    }
    if UNLIKELY(m_asks.size() > 20) {
      cerr << "m_asks size > 20" << endl;
      return false;
    }
    return true;
  }

  [[nodiscard]]
  auto getTimestamp() const -> uint64_t {
    return m_timestamp;
  }

  [[nodiscard]]
  auto getBestBid() const -> std::pair<double, uint64_t> {
    if UNLIKELY(m_bids.empty())
      return std::make_pair(0., 0);
    const auto bestBid = prev(m_bids.end());
    return std::make_pair(i2f(bestBid->first), bestBid->second);
  }

  [[nodiscard]]
  auto getBestAsk() const -> std::pair<double, uint64_t> {
    if UNLIKELY(m_asks.empty())
      return std::make_pair(0., 0);
    const auto bestAsk = m_asks.begin();
    return std::make_pair(i2f(bestAsk->first), bestAsk->second);
  }
};


int main() {
  using namespace std;
  using namespace rapidjson;
  Timer _main_timer("Overall");

  DepthSnapshot dom;

  // Output file
  std::ofstream bestbidask("huobi_dm_depth.out.txt");
  bestbidask << std::setprecision(8);

  // Im using cache to measure real "message" parsing performance.
  // This vector contains "message"s from logs.
  std::vector<string> huobi_dm_depth_messages;
  const std::regex base_regex(R"raw(current time: (\d+), message: (.+))raw");

  std::ifstream huobi_dm_depth("huobi_dm_depth.log", std::ios::in);
  //std::istringstream huobi_dm_depth(logs);
  if (!huobi_dm_depth) {
    cerr << "Cannot open stream. Set working directory to path where 'huobi_dm_depth.log' is." << endl;
    exit(1);
  }

  {
    Timer _timer("Parsing log file");
    std::string line;
    while (getline(huobi_dm_depth, line)) {
      std::smatch time_message_match;
      if (std::regex_search(line, time_message_match, base_regex)) {
        if (time_message_match.size() != 3) {
          clog << "Corrupted line? line: " << line << endl;
          for (auto &a : time_message_match) {
            clog << "Corrupted line? match: " << a << endl;
          }
          return 1;
        }

        string current_time = time_message_match[1].str();
        string message = time_message_match[2].str();
        huobi_dm_depth_messages.emplace_back(message);
      }
    }
  }

  {
    Timer _timer("Parsing " + to_string(huobi_dm_depth_messages.size()) + " messages");
    for (auto &message : huobi_dm_depth_messages) {
      bool success = dom.apply(message);
      if UNLIKELY(!success) {
        cerr << "Something bad happen. message: " << message << endl;
        return 1;
      }

      uint64_t ts = dom.getTimestamp();
      auto bid = dom.getBestBid();
      auto ask = dom.getBestAsk();
      bestbidask << ts << ", " << bid.first << ", " << bid.second << ", " << ask.first << ", " << ask.second << "\n";
    }
    std::cout << "Latency: " << (1e+3 * _timer.calculate() / static_cast<double>(huobi_dm_depth_messages.size()))
              << " ms per message"
              << endl;
  }

  return 0;
}
