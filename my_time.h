#pragma once
#include <chrono>
#include <functional>
#include <iostream>

namespace my_time {

//@brief  计算传入函数或者 lambda 表达式所耗时间.
//@usage
//- 传入函数名 GetTime(some_function);
//- 传入被lambda表达式包装的函数 GetTime([]{ some_function(arg1, arg2);});
inline void GetTime(std::function<void()> func) {
  std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
  std::chrono::duration<double> duration;
  start = std::chrono::high_resolution_clock::now();
  func();
  end = std::chrono::high_resolution_clock::now();
  duration = end - start;
  double sec = duration.count();
  std::cout << "Timer took " << sec << "s" << std::endl;
}
//参考：https://www.zhihu.com/question/54706884/answer/140689032

//@brief  加在作用域{}入口 析构时输出作用域内代码所用时间
struct Timer {
  std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
  std::chrono::duration<double> duration;
  Timer() { start = std::chrono::high_resolution_clock::now(); }
  ~Timer() {
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    double sec = duration.count();
    std::cout << "Timer took " << sec << "s" << std::endl;
  }
};
// 参考链接：https://zhuanlan.zhihu.com/p/361955426

}  // namespace my_time
