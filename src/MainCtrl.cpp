#include "MainCtrl.h"

using namespace CMEEROBOT;

MainCtrl::MainCtrl():
  main_thrd_(nullptr),
  proc_done_(false) {

  }

MainCtrl::~MainCtrl() {
  proc_done_ = true;
  if (nullptr != main_thrd_) {
    main_thrd_->join();
    delete main_thrd_;
    main_thrd_ = nullptr;
  }
}

Status MainCtrl::Init() {
  // TODO: do something about initializing EtherCAT
  main_thrd_ = new std::thread(&MainCtrl::ProcessLoop, this);
  return Status::OK;
}

Status MainCtrl::AddTask(Task t) {
  std::unique_lock<std::mutex> locker(mtx_);
  task_queue_.push(t);
  return Status::OK;
}

Status MainCtrl::ClearAll() {
  std::unique_lock<std::mutex> locker(mtx_);
  std::queue<Task> empty;
  std::swap(task_queue_, empty);
  return Status::OK;
}

void MainCtrl::ProcessLoop() {
  while (!proc_done_) {
    {
      std::cout << "Looping..." << std::endl;
      std::unique_lock<std::mutex> locker(mtx_);
      if (0 != task_queue_.size()) {
        Task cur_task = task_queue_.front();
        task_queue_.pop();
        // TODO: exec cur_task though EtherCAT
      }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}
