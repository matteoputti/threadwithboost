#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <iostream>
using namespace std;

int secondsElapsed = 0;
boost::mutex m;
boost::condition_variable_any cond;

void wait(int seconds)
{
	boost::this_thread::sleep_for(boost::chrono::seconds(seconds));
}

void increaseSeconds()
{

	for(int i=0;i<3;i++)
	{
		boost::unique_lock<boost::mutex> lock{ m };
		wait(1);//wait for one second
		secondsElapsed++;
		cond.notify_all();
		cond.wait(m);
	}
	cond.notify_all();
}

void printSeconds()
{
	for(int i=0;i<3;i++)
	{
		boost::unique_lock<boost::mutex> lock{ m };
		cout << "Seconds elapsed: " << secondsElapsed << endl;
		cond.notify_all();
		cond.wait(m);
	}
	cond.notify_all();
}

int main()
{
	boost::thread t(increaseSeconds);
	boost::thread t2(printSeconds);
	t.join();
	t2.join();
	cout << "\a" << endl;
	return EXIT_SUCCESS;
}