/*

  ___                                 _      _       _ 
 |_ _|_ __   ___ ___  _ __ ___  _ __ | | ___| |_ ___| |
  | || '_ \ / __/ _ \| '_ ` _ \| '_ \| |/ _ \ __/ _ \ |
  | || | | | (_| (_) | | | | | | |_) | |  __/ ||  __/_|
 |___|_| |_|\___\___/|_| |_| |_| .__/|_|\___|\__\___(_)
                               |_|                     

*/

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <utility>
#include <unordered_set>

class start {
public:
  long r;
  long c;
  std::string str;
  start(const long &r_, const long &c_, const std::string &str_) {
    r = r_;
    c = c_;
    str = str_;
  }
};

void lcsubsqc(std::string str1, std::string str2) {
  long r, c;
  long oldr, oldc;
  long rtemp, ctemp;
  long rlen, clen;
  long clim, rlim;
  long i, j;
  bool stopRow, stopCol;
  long count = 0;
  std::string maxStr = "";
  std::string temp, str, tempStr;
  std::unordered_set<char> cs;
  std::queue<start> q;

  if(str1.size() && str2.size()) {
    // us.insert("0,0");
    q.push(start(0, 0, ""));
  }
  while(q.size()) {
    r = q.front().r;
    c = q.front().c;
    str = q.front().str;
    q.pop();

    rlen = str1.size() - r;
    clen = str2.size() - c;
    if(clen > rlen) {
      i = 0;
      j = clen - rlen;
    } else {
      j = 0;
      i = rlen - clen;
    }
    clim = c + j;
    rlim = r + i;
    stopRow = false;
    stopCol = false;
    oldr = -1;
    oldc = -1;
    cs.clear();
    while(rlim < str1.size() && clim < str2.size()) {
      // down
      if(!stopRow) {
        for(long p = r; p <= rlim; p++) {
          if(cs.count(str1.at(p)) == 0 && str1.at(p) == str2.at(clim)) {
            // stopRow = true;
            cs.insert(str1.at(p));
            ctemp = clim + 1;
            rtemp = p + 1;
            tempStr = str + str1.at(p);
            if(tempStr.size() > maxStr.size()) {
              maxStr = tempStr;
            }
            if(rtemp < str1.size() && ctemp < str2.size() && oldr != rtemp && oldc != ctemp) {
              oldr = rtemp;
              oldc = ctemp;
              q.push(start(rtemp, ctemp, tempStr));
            }
            break;
          }
        }
      }
      // right
      if(!stopCol) {
        for(long p = c; p <= clim; p++) {
          if(cs.count(str2.at(p)) == 0 && str2.at(p) == str1.at(rlim)) {
            // stopCol = true;
            cs.insert(str2.at(p));
            rtemp = rlim + 1;
            ctemp = p + 1;
            tempStr = str + str2.at(p);
            if(tempStr.size() > maxStr.size()) {
              maxStr = tempStr;
            }
            if(rtemp < str1.size() && ctemp < str2.size() && oldr != rtemp && oldc != ctemp) {
              oldr = rtemp;
              oldc = ctemp;
              q.push(start(rtemp, ctemp, tempStr));
            }
            break;
          }
        }
      }
      // if(stopRow && stopCol) {
      //   break;
      // }
      clim++;
      rlim++;
    }
  }
  std::cout << "Subsequence is: " << maxStr << std::endl;
  std::cout << "Subsequence size: " << maxStr.size() << std::endl;
}

int main() {
  std::string s1 = "xaab";
  std::string s2 = "abcdxaa";
  // lcsubsqc(s1, s2);
  // lcsubsqc(s2, s1);
  // lcsubsqc("abcdxaab", "abcdabcdxaa");
  // lcsubsqc("abcdabcdxaa", "abcdxaab");
  // lcsubsqc("abcbdab", "bdcab");
  // lcsubsqc("bdcab", "abcbdab");
  // lcsubsqc("ylqpejqbalahwr", "yrkzavgdmdgtqpg");
  // lcsubsqc("yrkzavgdmdgtqpg", "ylqpejqbalahwr");
  // lcsubsqc("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
  // lcsubsqc("lmrejgzsbqpkdonytkbknstsxifofmrktcpq", "hklcrebcjipetgnmlqvijovmlgripwratarmt");
  // lcsubsqc("hklcrebcjipetgnmlqvijovmlgripwratarmt", "lmrejgzsbqpkdonytkbknstsxifofmrktcpq");
  lcsubsqc("zelohidwdcxilkvytazgfozonwrkbalcpizgtmzuhkbsfefshmtctuvc", "rwjmzoncvihmlmvgdujopwrajuxmjefonivyvkncnwnkjaxkritkporsj");
  return 0;
}