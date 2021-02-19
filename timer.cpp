#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <iostream>
using namespace std;

void wait(int seconds)
{
	boost::this_thread::sleep_for(boost::chrono::seconds(seconds));
}

void timer(int seconds)
{
	while(seconds>0)
	{
		wait(1);//wait for one second
		cout << "Seconds remaining: " << seconds << endl;
		seconds--;
	}
}

int main()
{
	int seconds;
	cout << "Enter seconds for the timer: ";
	cin >> seconds;
	boost::thread t(timer,seconds);
	t.join();
	cout << "Timer elapsed!\a" << endl;
	return EXIT_SUCCESS;

}