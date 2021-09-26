#include<bits/stdc++.h>
using namespace std;

class Slot{
public:
	int slot_number;
	bool isFree;
	string vehicle_number;
	int driver_age;

	Slot(int slot_number = 0){
		this->slot_number = slot_number;
		isFree = true;
		vehicle_number = "";
		driver_age = 0;
	}
};

class ParkingLot{
private:
	int total_parking_slot;
	map<int, Slot*> all_slots;
	map<string, Slot*> slot_from_vehicle_number;
public:
	ParkingLot(int total_parking_slot){
		this->total_parking_slot = total_parking_slot;
		for(int i = 1 ; i <= total_parking_slot ; i++){
			Slot* a = new Slot(i);
			all_slots[i] = a;
		}
	}

	void parkVehicle(string vehicle_number, int driver_age){
		int free_slot = 0;
		for(auto i:all_slots){
			if(i.second->isFree && i.second->slot_number!=0){
				free_slot = i.second->slot_number;
				break;
			}
		}

		if(free_slot == 0){
			cout<<"There is no empty space in the Parking";
		} else {
			Slot* temp = all_slots[free_slot];
			temp->vehicle_number = vehicle_number;
			temp->driver_age = driver_age;
			temp->isFree = false;
			slot_from_vehicle_number[vehicle_number] = temp;
			cout<<"Car with vehicle registration number \""<<vehicle_number<<"\" has been parked at slot number "<<free_slot;
		}
	}

	void getSlotsFromAge(int driver_age){
		vector<int> slots;

		for(auto i:slot_from_vehicle_number){
			if(i.second->isFree == false && i.second->driver_age == driver_age){
				slots.push_back(i.second->slot_number);
			}
		}

		sort(slots.begin(), slots.end());
		for(int i = 0 ; i < slots.size() ; i++){
			if(i!=0)
			cout<<",";

			cout<<slots[i];
		}
	}

	void getSlotFromVehicleNumber(string vehicle_number){
		cout<<slot_from_vehicle_number[vehicle_number]->slot_number;
	}

	void freeSlot(int slot_number){
		Slot* temp = all_slots[slot_number];
		if(temp->isFree){
            cout<<"Slot already Vacant";
            return;
		}

		string vehicle_in_slot = temp->vehicle_number;
		int driver_age_in_slot = temp->driver_age;

		temp->isFree = true;
		temp->vehicle_number = "";
		temp->driver_age = 0;

		slot_from_vehicle_number.erase(vehicle_in_slot);
		cout<<"Slot number "<<slot_number<<" vacated, the car with vehicle registration number \""<<vehicle_in_slot<<"\" left the space, the driver of the car was of age "<<driver_age_in_slot;
	}

	void vehicleNumberFromAge(int driver_age){
		vector<int> slots;

		for(auto i:slot_from_vehicle_number){
			if(i.second->isFree == false && i.second->driver_age == driver_age){
				slots.push_back(i.second->slot_number);
			}
		}

		sort(slots.begin(), slots.end());
		for(int i = 0 ; i < slots.size() ; i++){
			if(i!=0)
			cout<<",";

			cout<<all_slots[slots[i]]->vehicle_number;
		}
	}
};

int main()
{
	#ifndef ONLINE_JUDGE
	freopen("input.txt","r", stdin);
	#endif

	ParkingLot* parking_lot;

	while(1){
		string s;
		getline(cin,s);

		if(s=="")
		break;

		stringstream str(s);
		string word;
		str>>word;

		if(word == "Create_parking_lot")
		{
			str>>word;
			int total_parking_slot = stoi(word);

			parking_lot = new ParkingLot(total_parking_slot);
			cout<<"Created parking of "<< total_parking_slot <<" slots";
		}
		else if(word == "Park")
		{
			str>>word;
			string vehicle_number = word;
			str>>word;
			if(word == "driver_age"){
				str>>word;
				int driver_age = stoi(word);
				parking_lot->parkVehicle(vehicle_number,driver_age);
			} else{
				cout<<"Invalid Command";
			}
		}
		else if(word == "Slot_numbers_for_driver_of_age")
		{
			str>>word;
			int driver_age = stoi(word);
			parking_lot->getSlotsFromAge(driver_age);
		}
		else if(word == "Slot_number_for_car_with_number")
		{
			str>>word;
			string vehicle_number = word;
			parking_lot->getSlotFromVehicleNumber(vehicle_number);
		}
		else if(word == "Leave")
		{
			str>>word;
			int slot_number = stoi(word);
			parking_lot->freeSlot(slot_number);
		}
		else if(word == "Vehicle_registration_number_for_driver_of_age")
		{
			str>>word;
			int driver_age = stoi(word);
			parking_lot->vehicleNumberFromAge(driver_age);
		}
		else
		{
			cout<<"Invalid Command";
		}
		cout<<endl;
	}

}
