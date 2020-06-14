#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <atomic>

namespace CMEEROBOT {
  enum class Status {
    OK, 
    FAILED,     
  };
  typedef struct tagPosition {
    double x;
    double y;
    double z;
    double pitch;

    double roll;
    double yaw;
  } Pos;

  typedef struct tagTask {
    int32_t id;
    int8_t task_type;
    Pos start;
    Pos end;
    double target;

  } Task;

  class MainCtrl {
    public:
      MainCtrl();
      ~MainCtrl();

      Status Init();

      Status AddTask(Task t);

      Status ClearAll();

    private:
      std::queue<Task> task_queue_;

      std::thread* main_thrd_;

      std::mutex mtx_;

      std::atomic<bool> proc_done_;

      void ProcessLoop();
  };

}
