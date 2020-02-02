//Burak Bozdað

#include <iostream>
#include <fstream>
#include <string>

#define CAP 1000000 // MAX 1M events are allowed.

using namespace std;

class event{
public: //Variables are defined as public since this code is only for this homework :)
	int time;
	string name;
	char type;
};

class minHeap{
	event* array;
	int size;
public:
	//Constructor
	minHeap(){
		array = new event[CAP];
		size = 0;
	};
	
	//Functions
	void insert(event e){
		if(size == CAP){
			cout << "The heap capacity exceeds the limit. Can't insert the event." << endl;
			return;
		}
		
		//Inserting an event at the end
		++size;
		int i = size - 1;
		array[i] = e;
		
		//Fixing minimum heap property
		while(i != 0 && array[(i - 1) / 2].time > array[i].time){
			event temp = array[(i - 1) / 2];
			array[(i - 1) / 2] = array[i];
			array[i] = temp;
			--i;
			i /= 2;
		}
	};
	
	//Extracting the next event from the heap
	event nextEvent(){
		if(size <= 0){
			event error;
			error.time = -1;
			error.type = 'i';
			return error;
		}else if(size == 1){
			--size;
			return array[0];
		}
		
		//Removing the next event and returning
		event next = array[0];
		array[0] = array[size - 1];
		--size;
		heapify(0);
		return next;
	};
	
	//Heapifying a subtree within a given index
	void heapify(int i){
		int subRoot = i;
		if(2 * i + 1 < size && array[2 * i + 1].time < array[i].time){
			subRoot = 2 * i + 1;
		}
		if(2 * i + 2 < size && array[2 * i + 2].time < array[subRoot].time){
			subRoot = 2 * i + 2;
		}
		if(subRoot != i){
			event temp = array[i];
			array[i] = array[subRoot];
			array[subRoot] = temp;
			heapify(subRoot);
		}
	};
	
	//Getters
	event root(){ return array[0]; };
	int getSize(){ return size; };
};

int main(int argc, char** argv)
{
	//Error checking
	if(argc != 2) {
		cout << "Invalid arguments." << endl;
		return 1;
	}
	
	ifstream read(argv[1]);
	if(!read.is_open()){
		cout << "Error opening file." << endl;
		return 1;
	}
	
	//Reading file and inserting events to the heap
	minHeap events;
	string name;
	int s, e, line = 0;
	while(read >> name >> s >> e){
		++line;
		if(s >= e){
			cout << "Event start time must be lower than end time. Line " << line << " is ignored." << endl;
			continue;
		}
		event e1;
		e1.time = s;
		e1.name = name;
		e1.type = 's';
		events.insert(e1);
		event e2;
		e2.time = e;
		e2.name = name;
		e2.type = 'e';
		events.insert(e2);
	}
	
	//Printing scheduler results in the correct order
	event next = events.nextEvent();
	int clock = 1;
	if(next.time == -1){
		cout << "TIME " << clock << ": NO MORE EVENTS, SCHEDULER EXITS" << endl;
		read.close();
		return 0;
	}
	while(1){
		while(next.time != clock){
			cout << "TIME " << clock << ": NO EVENT" << endl;
			++clock;
		}
		while(next.time == clock){
			if(next.type == 's'){
				cout << "TIME " << clock << ": " << next.name << " STARTED" << endl;
			}else if(next.type == 'e'){
				cout << "TIME " << clock << ": " << next.name << " ENDED" << endl;
			}
			next = events.nextEvent();
		}
		if(next.time == -1){
			cout << "TIME " << clock << ": NO MORE EVENTS, SCHEDULER EXITS" << endl;
			break;
		}
		++clock;
	}
	
	read.close();
	return 0;
}
