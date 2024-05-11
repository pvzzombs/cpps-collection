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
          // c = clim + 1;
          // r = p + 1;
          tempStr = str + str1.at(p);
          if(tempStr.size() > maxStr.size()) {
            maxStr = tempStr;
          }
          if(r < str1.size() && c < str2.size()) {
            q.push(start(p + 1, clim + 1, tempStr));
          }
          break;
        }
      }
      // right
      for(long p = c; p < clim; p++) {
        if(str2.at(p) == str1.at(rlim)) {
          stop = true;
          // r = rlim + 1;
          // c = p + 1;
          tempStr = str + str2.at(p);
          if(tempStr.size() > maxStr.size()) {
            maxStr = tempStr;
          }
          if(r < str1.size() && c < str2.size()) {
            q.push(start(rlim + 1, p + 1, tempStr));
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
  // lcsubsqc("abcdxaab", "abcdabcdxaa");
  // lcsubsqc("abcdabcdxaa", "abcdxaab");
  return 0;
}