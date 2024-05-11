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
  long rtemp, ctemp;
  long rlen, clen;
  long clim, rlim;
  long i, j;
  bool stop;
  long count = 0;
  std::string maxStr = "";
  std::string str, tempStr;
  std::queue<start> q;

  if(str1.size() && str2.size()) {
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
    while(rlim < str1.size() && clim < str2.size()) {
      // down
      stop = false;
      for(long p = r; p <= rlim; p++) {
        if(str1.at(p) == str2.at(clim)) {
          stop = true;
          ctemp = clim + 1;
          rtemp = p + 1;
          tempStr = str + str1.at(p);
          if(tempStr.size() > maxStr.size()) {
            maxStr = tempStr;
          }
          if(rtemp < str1.size() && ctemp < str2.size()) {
            q.push(start(rtemp, ctemp, tempStr));
          }
          break;
        }
      }
      // right
      for(long p = c; p < clim; p++) {
        if(str2.at(p) == str1.at(rlim)) {
          stop = true;
          rtemp = rlim + 1;
          ctemp = p + 1;
          tempStr = str + str2.at(p);
          if(tempStr.size() > maxStr.size()) {
            maxStr = tempStr;
          }
          if(rtemp < str1.size() && ctemp < str2.size()) {
            q.push(start(rtemp, ctemp, tempStr));
          }
          break;
        }
      }
      if(stop) {
        break;
      }
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
  lcsubsqc(s1, s2);
  lcsubsqc(s2, s1);
  lcsubsqc("abcdxaab", "abcdabcdxaa");
  lcsubsqc("abcdabcdxaa", "abcdxaab");
  lcsubsqc("abcbdab", "bdcab");
  lcsubsqc("bdcab", "abcbdab");
  return 0;
}