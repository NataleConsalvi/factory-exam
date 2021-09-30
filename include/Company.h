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
    vector<Item> travel;
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

        void set_truck(int trip_id, unordered_map<string,int>& items, bool t){
            //true = scarico
            if(t){
                if(this->trucks[trip_id]->items.size() == 0){
                    throw std::invalid_argument(string("The truck is empty!"));
                    //Lancia eccezione, specifica anche se va in negativo!
                }else{
                    if(this->trucks[trip_id]->items["mele"] < items["mele"]){
                        throw std::invalid_argument(string("There are not enough apples!"));
                    }
                    if(this->trucks[trip_id]->items["fragole"] < items["fragole"]){
                        throw std::invalid_argument(string("There are not enough strawberries!"));
                    }
                    if(this->trucks[trip_id]->items["arance"] < items["arance"]){
                        throw std::invalid_argument(string("There are not enough oranges!"));
                    }
                    this->trucks[trip_id]->items["mele"] -= items["mele"];
                    this->trucks[trip_id]->items["fragole"] -= items["fragole"];
                    this->trucks[trip_id]->items["arance"] -= items["arance"];
                }
            }else{ //carico
                if(this->trucks[trip_id]->items.size() == 0){
                    this->trucks[trip_id]->items = items;
                }else{
                    this->trucks[trip_id]->items["mele"] += items["mele"];
                    this->trucks[trip_id]->items["fragole"] += items["fragole"];
                    this->trucks[trip_id]->items["arance"] += items["arance"];
                }
            }

        }

        void add_travel(int trip_id ,string place, int time){
            this->trucks[trip_id]->travel.push_back({place, time});
        }

        void load(int trip_id, string place, unordered_map<string,int> items){
            cout << "DEBUG: plan load for trip " << std::to_string(trip_id) << " at location " << place << endl;
            //setting content truck (false = scarico)
            set_truck(trip_id, items, false);
            //setting time of truck's travel
            int time = (items["mele"] + items["arance"] + items["fragole"])*MIN_DELAY;
            this->trucks[trip_id]->time += time;
            //setting content warehouse (true per rimuovere da magazzino)
            set_warehouse(place, items, true);
            add_travel(trip_id, place, time);

            cout << "DEBUG: goods on truck are now:" << map2str(this->trucks[trip_id]->items) << endl;
        }

        void check_in(int trip_id, string place){
            cout << "DEBUG: plan check_in for trip " << std::to_string(trip_id) << " at location " << place << endl;
            this->trucks[trip_id]->time += this->trucks[trip_id]->items["mele"]*this->customs[place]["mele"];
            this->trucks[trip_id]->time += this->trucks[trip_id]->items["fragole"]*this->customs[place]["fragole"];
            this->trucks[trip_id]->time += this->trucks[trip_id]->items["arance"]*this->customs[place]["arance"];
            int time =  this->trucks[trip_id]->items["mele"]*this->customs[place]["mele"] + this->trucks[trip_id]->items["fragole"]*this->customs[place]["fragole"] + this->trucks[trip_id]->items["arance"]*this->customs[place]["arance"]; 
            add_travel(trip_id, place, time);
            
        }

        void rest(int trip_id, const string place){
            cout << "DEBUG: plan rest for trip " << std::to_string(trip_id) << " at location " << place << endl;
            this->trucks[trip_id]->time += 8*60;
            add_travel(trip_id, place, 8*60);
        }

        void ship(int trip_id, string place, unordered_map<string,int> items){
            cout << "DEBUG: plan ship for trip " << std::to_string(trip_id) << " at location " << place << endl;
            //setting content truck (true = carico)
            set_truck(trip_id, items, true);

            //setting time of truck's travel
            int time = (items["mele"] + items["arance"] + items["fragole"])*MIN_DELAY;
            this->trucks[trip_id]->time += time;
            
            //setting content warehouse
            set_warehouse(place, items, false);
            add_travel(trip_id, place, time);
            cout << "DEBUG: goods on truck are now:" << map2str(this->trucks[trip_id]->items) << endl;
        }

        string trip_to_string(int trip_id){
            string s;
            s += "\nTRIP " + std::to_string(trip_id) + "\n";
            s += "      Stop:";
            for(Item place : this->trucks[trip_id]->travel){
                s += "\t\t" + place.name;
            }
            s += "\nmin attesa:";
            for(Item place : this->trucks[trip_id]->travel){
                s += "\t\t";
                for(int i = 0; i < place.name.size() - 3; i++){
                    s += " ";
                }
                s += std::to_string(place.size);
            }
            return s;

        }

};

#endif //COMPANY_H