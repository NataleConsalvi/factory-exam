#ifndef COMPANY_H
#define COMPANY_H

#include "deliv.h"

struct Item{
    string name;
    int size;
};

struct Camion{
    int time;
    unordered_map<string, int> items;
};

class Company{

    private:
        unordered_map<string, unordered_map<string,int>> warehouses;
        unordered_map<string, unordered_map<string,int>> customs;
        vector<Camion*> trucks;
        int travels;
    
    public:

        Company(){
            this->travels = 0;
        }

        void set_warehouse(unordered_map<string,int>& items){
            if(items.count("mele") == 0){
                items["mele"] = 0;
            }
            if(items.count("arance") == 0){
                items["arance"] = 0;
            }
            if(items.count("fragole") == 0){
                items["fragole"] = 0;
            }
        }

        void set_customs(unordered_map<string,int>& items){
            if(items.count("mele") == 0){
                items["mele"] = MIN_DELAY;
            }
            if(items.count("arance") == 0){
                items["arance"] = MIN_DELAY;
            }
            if(items.count("fragole") == 0){
                items["fragole"] = MIN_DELAY;
            }
        }

        void add_warehouse(const string name, unordered_map<string,int> items){
            cout << "DEBUG: adding warehouse " << name << endl;
            if(warehouses.count(name) == 1){
                throw std::invalid_argument("Warehouse already present!");
            }
            this->set_warehouse(items);
            this->warehouses[name] = items;
        }

        void add_customs(const string name, unordered_map<string,int> items){
            if(customs.count(name) == 1){
                throw std::invalid_argument("Customs already present!");
            }
            this->set_customs(items);
            this->customs[name] = items;
        }

        int create_trip(){
            
            int ret = this->travels;
            Camion* new_tir = new Camion;
            this->trucks.push_back(new_tir);
            this->travels++;
            return ret;
        }

        void set_warehouse(const string place, unordered_map<string,int> items, const bool t){
            //ADD CONTROLLI
            if(t){
                this->warehouses[place]["mele"] -= items["mele"];
                this->warehouses[place]["fragole"] -= items["fragole"];
                this->warehouses[place]["arance"] -= items["arance"];
            }else{
                this->warehouses[place]["mele"] += items["mele"];
                this->warehouses[place]["fragole"] += items["fragole"];
                this->warehouses[place]["arance"] += items["arance"];
            }

        }

        void load(int trip_id, string place, unordered_map<string,int> items){
            cout << "DEBUG: plan load for trip " << std::to_string(trip_id) << " at location " << place << endl;
            //setting content truck 
            if(this->trucks[trip_id]->items.size() == 0){
                this->trucks[trip_id]->items = items;
            }else{
                this->trucks[trip_id]->items["mele"] += items["mele"];
                this->trucks[trip_id]->items["fragole"] += items["fragole"];
                this->trucks[trip_id]->items["arance"] += items["arance"];
            }
            //setting time of truck's travel
            this->trucks[trip_id]->time += (items["mele"] + items["arance"] + items["fragole"])*MIN_DELAY;
            //setting content warehouse (true per rimuovere da magazzino)
            set_warehouse(place, items, true);

            cout << "DEBUG: goods on truck are now:" << map2str(this->trucks[trip_id]->items) << endl;
        }

        void check_in(int trip_id, string place){
            cout << "DEBUG: plan check_in for trip " << std::to_string(trip_id) << " at location " << place << endl;
            this->trucks[trip_id]->time += this->trucks[trip_id]->items["mele"]*this->customs[place]["mele"];
            this->trucks[trip_id]->time += this->trucks[trip_id]->items["fragole"]*this->customs[place]["fragole"];
            this->trucks[trip_id]->time += this->trucks[trip_id]->items["arance"]*this->customs[place]["arance"];
            
        }

        void rest(int trip_id, const string place){
            cout << "DEBUG: plan rest for trip " << std::to_string(trip_id) << " at location " << place << endl;
            this->trucks[trip_id]->time += 8*60;
        }

        void ship(int trip_id, string place, unordered_map<string,int> items){
            cout << "DEBUG: plan ship for trip " << std::to_string(trip_id) << " at location " << place << endl;
            //setting content truck 
            if(this->trucks[trip_id]->items.size() == 0){
                //Lancia eccezione, specifica anche se va in negativo!
            }else{
                this->trucks[trip_id]->items["mele"] -= items["mele"];
                this->trucks[trip_id]->items["fragole"] -= items["fragole"];
                this->trucks[trip_id]->items["arance"] -= items["arance"];
            }
            //setting time of truck's travel
            this->trucks[trip_id]->time += (items["mele"] + items["arance"] + items["fragole"])*MIN_DELAY;
            //setting content warehouse
            set_warehouse(place, items, false);

            cout << "DEBUG: goods on truck are now:" << map2str(this->trucks[trip_id]->items) << endl;
        }






};

#endif //COMPANY_H