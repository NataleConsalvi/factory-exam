

#include "deliv.h"
#include "Company.h"


int main() {

    Company company;

    company.add_warehouse("Trento", {{"mele", 500}, {"fragole", 1000}});  // NOTA: NEI MAGAZZINI QUESTO E' IL *NUMERO DI CASSE*
    company.add_customs("Milano", {{"mele", 5}, {"fragole", 3}});  // NOTA: NELLE CUSTOMS QUESTO E' IL *DELAY* IN MINUTI PER CASSA
    company.add_customs("Dusseldorf", {{"fragole", 1}});
    company.add_customs("Parigi", {{"fragole", 2}});
    company.add_customs("Oslo", {{"mele", 4}, {"fragole", 2}});
    company.add_warehouse("Londra", {{"fragole", 1000}, {"mele",2000}});   
    company.add_warehouse("Dusseldorf", {{"fragole", 3000}, {"mele", 4000}, {"arance", 6000}});   

    // NOTA: le connection potrebbero servire SOLO per la seconda parte se volete considerare anche la lunghezza strade
    /*
    company.add_connection("Trento", "Milano", 40);
    company.add_connection("Milano", "Dusseldorf", 100);
    company.add_connection("Dusseldorf", "Parigi", 300);
    company.add_connection("Parigi", "Londra", 200);    
    */
    
    int trip_id = company.create_trip();
    
    cout << "PLANNING..." << endl;
    company.load(trip_id, "Trento", {{"mele",10}, {"fragole",7}});  // carica 10 casse di mele e 7 di fragole dal magazzino
    company.check_in(trip_id, "Milano");      // ferma alla dogana    
    company.check_in(trip_id, "Dusseldorf");     
    company.rest(trip_id, "Parigi");         // riposo previsto 8h
    company.check_in(trip_id, "Parigi");        
    
    company.ship(trip_id, "Londra", {{"mele",4}, {"fragole", 2}});   // consegna casse al magazzino
    company.check_in(trip_id, "Oslo");  // ferma alla dogana    
    company.ship(trip_id, "Dusseldorf", {{"mele", 6}, {"fragole", 2}});     // consegna  al magazzino        
    company.rest(trip_id, "Trento"); 
    
    cout << company.trip_to_string(trip_id) << endl;
     
    cout << endl <<"ACTUAL:" << endl;
    company.load(trip_id, "Trento", {{"mele",9}, {"fragole",8}}, 200);  // NOTA: qua specifichiamo anche il tempo (minuti)    
    company.check_in(trip_id, "Milano", 130);      // ferma alla dogana
    company.check_in(trip_id, "Dusseldorf", 200); 
    company.rest(trip_id, "Parigi", 7*60); 
    company.check_in(trip_id, "Parigi", 60);    
    company.ship(trip_id, "Londra", {{"mele", 5}, {"fragole", 1}}, 70);   // consegna al magazzino
    company.check_in(trip_id, "Oslo", 100);  // ferma alla dogana
    company.ship(trip_id, "Dusseldorf", {{"mele", 1}, {"fragole", 1}}, 120);
    company.rest(trip_id, "Trento", 6*60); 

    cout << company.trip_to_string(trip_id) << endl;
    
    return 0;
};
