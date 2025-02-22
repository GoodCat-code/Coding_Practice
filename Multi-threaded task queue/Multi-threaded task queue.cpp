#include <iostream>
#include <thread>
#include <functional>
#include <queue>
#include <mutex>

using namespace std;

// create task
void task() {
	this_thread::sleep_for(chrono::milliseconds(500));
	cout << "TASK worked" << endl;
}

class TaskQueue {
public:
	void push(function<void()> task) {
		lock_guard<mutex> lock(mtx);
		tasks_queue.push(task);
	}

	void work() {
		while (true)
		{
			lock_guard<mutex> lock(mtx);
			while (!tasks_queue.empty())
			{
				function<void()> f;
				f = tasks_queue.front();
				tasks_queue.pop();
				f();
			}
		}
	}

private:
	queue<function<void()>> tasks_queue; // create queue
	mutex mtx;
};

int main()
{
	TaskQueue TQ;

	thread worker(&TaskQueue::work, &TQ);

	thread th1(&TaskQueue::push, &TQ, []() {task(); });		// push task into the queue
	thread th2(&TaskQueue::push, &TQ, []() {task(); });		// push task into the queue

	th1.join();
	th2.join();

	this_thread::sleep_for(chrono::milliseconds(2000));

	thread th3(&TaskQueue::push, &TQ, []() {task(); });
	th3.join();

	worker.join();
}
