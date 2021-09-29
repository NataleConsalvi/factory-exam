
# Esame Tecniche di Programmazione Avanzata 13 Luglio 2021 - Ditta spedizioni

Una ditta di spedizioni pianifica dei viaggi in camion che prevedono l'attraversamento di varie città. 

Una città può avere un magazzino della ditta, una dogana (o entrambe). La ditta gestisce vari beni (es mele, fragole, arance)

I magazzini sono di proprietà della ditta e contengono una certa quantità di casse per ogni bene. Quando una singola cassa viene caricata / scaricata viene impiegato un tempo costante `MIN_DELAY = 10` minuti.

Le dogane **non** contengono casse ma effettuano controlli. La ditta ha a disposizione delle stime sul tempo impiegato da 
ciascuna dogana per esaminare una cassa di ciascun tipo di bene. Se non viene specificata nessuna stima per un bene, assumiamo MIN_DELAY.

Per legge un camionista deve riposare almeno 8h*60 minuti al giorno. Il camionista può riposare nella città che vuole.

La ditta vuole stimare il tempo necessario ad un camion per effettuare un certo tragitto. 

Fatta la stima, il camion parte e segnala via via il tempo effettivo trascorso durante la permanenza nelle varie tappe, che può cambiare per motivi vari (camion trattenuto di più alla dogana, autista che ha dormito meno del previsto).

Durante il viaggio, la ditta vuole avere una visualizzazione che consenta di comparare il piano originale 
con l'esecuzione attuale.

## Modello dati

- assumiamo che nessuna città abbia lo stesso nome di un'altra
- assumiamo che il numero e sequenza di città di stop previste / attuali siano identiche

## Metodologia:

- **IMPORTANTE**: TUTTO il codice può essere implementato negli header .h come inline, **NON** perdere tempo a creare cpp e/o separare il corpo dei metodi
- Si suppone che l'utente sviluppatore interagisca col software solo attraverso la classe Company: non dovrebbe essergli possibile manomettere le classi interne, quindi se esponete qualcosa usate opportuni meccanismi di protezione (incapsulamento / const)
- Detto ciò, **NON** perdete tempo a creare classi super incapsulate con getter / setter, se vi serve qualche struttura di appoggio semplicemente usate una struct che di default ha già tutto public
- vi vengono forniti un abbozzo di main.cpp e la libreria deliv.h con qualche struttura e funzione di utilità
- La minimizzazione del codice attraverso scomposizione in classi, riuso metodi, etc sarà premiata
- l'uso di puntatori e allocazione dinamica verrà opportunamente premiato in fase di valutazione
- NON implementare algoritmi di esplorazione grafi tipo minimizzazione percorrenza, routing, etc
- il focus sarà sulla correttezza, comunque chi userà strutture efficienti (mappe, indici con puntatori, etc) sarà opportunamente premiato


## Che fare:

1. Implementare `Company` e `trip_to_string` in modo da mostrare almeno la parte del planning.   Tenere traccia delle casse sul camion durante il viaggio per poter calcolare opportunamente i delay. Proseguire poi con mostrare i tempi attuali.

- **NOTA 1**: negli esempi del main, per evitare di avere doppi metodi per planning / esecuzione, si è preferito avere metodi singoli con argomento opzionale `int minutes=-1` alla fine, così potete discriminare tra planning / esecuzione.
- **NOTA 2**: Modificare lo stato dei magazzini solo in fase di attuazione del trip.
- **NOTA 3**: Per fare una stampa opportunamente giustificata importare `<iomanip>` e usare cose tipo `cout << setw(11) << campo1 << setw(11) << campo2` 

2. **Una volta fatto quanto sopra**, si potrebbero memorizzare e mostrare nella `trip_to_string`:

    - un costo per non rispetto delle deadline prefissate (anche multe per mancanza riposo 8h guidatore)
    - tempo di permanenza in strade
    - considerare scadenza merci (pesci, uova, ..), con conseguente perdita di beni
    - mostrare il giorno di arrivo


**IMPORTANTE 1**: sicuramente non avrete il tempo di implementare a dovere tutto quanto, piuttosto scegliete alcuni aspetti e aggiungete dei test **significativi** (max 100 righe di codice) che dimostrino l'efficacia della vostra soluzione. 

**IMPORTANTE 2**: ai fini dell'esame quando viene incontrata una condizione d'errore è sufficiente che che il programma termini (i.e. sollevando eccezioni), non perdete tempo a fare gestione accurata degli errori (blocchi try) che vi porterebbero via troppo tempo.

## Esempio di esecuzione

**NOTA**: è **solo** un abbozzo di display del main, ogni cosa va opportunamente valutata

```
DEBUG: Adding warehouse Trento
DEBUG: Adding warehouse Londra
DEBUG: Adding warehouse Dusseldorf
DEBUG: Adding connection from Trento to Milano
DEBUG: Adding connection from Milano to Dusseldorf
DEBUG: Adding connection from Dusseldorf to Parigi
DEBUG: Adding connection from Parigi to Londra
DEBUG: creating trip 0
PLANNING...
DEBUG: plan load for trip 0 at location Trento
DEBUG   goods to load: {
 fragole : 7,
 mele : 10
}
DEBUG: goods on truck are now:{
 mele : 10,
 fragole : 7
}
DEBUG: plan check_in for trip 0 at location Milano
DEBUG: plan check_in for trip 0 at location Dusseldorf
DEBUG: plan rest for trip 0 at location Parigi
DEBUG: plan check_in for trip 0 at location Parigi
DEBUG: plan ship for trip 0 at location Londra
DEBUG: goods to ship: {
 fragole : 2,
 mele : 4
}
DEBUG: goods on truck are now:{
 mele : 6,
 fragole : 5
}
DEBUG: plan check_in for trip 0 at location Oslo
DEBUG: plan ship for trip 0 at location Dusseldorf
DEBUG: goods to ship: {
 fragole : 2,
 mele : 6
}
DEBUG: goods on truck are now:{
 mele : 0,
 fragole : 3
}
DEBUG: plan rest for trip 0 at location Trento
TRIP 0

        Stop:      Trento      Milano  Dusseldorf      Parigi      Parigi      Londra        Oslo  Dusseldorf      Trento
    permanenza
        attesa         170          71         107         480         114          60          34          80         480
     effettiva

min cumulativi
        attesi         170         241         348         828         942        1002        1036        1116        1596
     effettivi

ACTUAL:
DEBUG:  load for trip 0 at location Trento
DEBUG   goods to load: {
 fragole : 8,
 mele : 9
}
DEBUG: goods on truck are now:{
 mele : 9,
 fragole : 8
}
DEBUG:  check_in for trip 0 at location Milano
DEBUG:  check_in for trip 0 at location Dusseldorf
DEBUG:  rest for trip 0 at location Parigi
DEBUG:  check_in for trip 0 at location Parigi
DEBUG:  ship for trip 0 at location Londra
DEBUG: goods to ship: {
 fragole : 1,
 mele : 5
}
DEBUG: goods on truck are now:{
 mele : 4,
 fragole : 7
}
DEBUG:  check_in for trip 0 at location Oslo
DEBUG:  ship for trip 0 at location Dusseldorf
DEBUG: goods to ship: {
 fragole : 1,
 mele : 1
}
DEBUG: goods on truck are now:{
 mele : 3,
 fragole : 6
}
DEBUG:  rest for trip 0 at location Trento
TRIP 0

        Stop:      Trento      Milano  Dusseldorf      Parigi      Parigi      Londra        Oslo  Dusseldorf      Trento
    permanenza
        attesa         170          71         107         480         114          60          34          80         480
     effettiva         200         130         200         420          60          70         100         120         360

min cumulativi
        attesi         170         241         348         828         942        1002        1036        1116        1596
     effettivi         200         330         530         950        1010        1080        1180        1300        1660

DEBUG: Company destructor
```