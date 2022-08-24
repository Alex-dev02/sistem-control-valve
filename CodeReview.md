# Code review

## 2022-07-22

### Code structure

- [x] rename pe executabile sa-thermostat, sa-valve
- [x] de vreme ce ai folosit directoare separate fă biblioteci separate pentru fiecare folder (networking)
- [x] folosește Include paths (vezi de exemplu acest [item din SO](https://stackoverflow.com/questions/13703647/how-to-properly-add-include-directories-with-cmake)).
- [x] folosește naming consecvent pentru fișiere. Litere mici, și pentru fișiere și pentru directoare.
- [ ] include doar ce e necesar. Include minimul necesar în headere - include doar ce ai nevoie în fiecare unitate de compilare.
- [ ] Functia care extrage variabilele din request trebuie regandita

### Valve/Thermostat

- [x] termostatul crash-uieste daca primeste requesturi in care variabilele sunt numite incorect
- [x] ce se intampla daca primim o variabila fara valoare in path + unit test pe ea
- [x] `void SetTemperature(float temperature);` și `void IncrementTemperature();` sunt publice. De ce?
- [x] Îmi e neclară relația dintre clasa Valve și clasa Router. Valva este un Router? Are un router? Ar trebui să fie derivată din Router?
- [x] Pentru Router este un tip de date complex ar trebui să nu poată fi copiat - operațiunea de copiere nu ar trebui să aibă sens pentru Router. Tu faci o copie în main, dar dacă adaug on-the-fly noi endpoints în Router? `main` nu le va vedea.
- [x] main-ul de la termostat și valvă seamănă foarte mult. Se poate refolosi acel cod?
- [x] Thermostat::SetTarget are prea multe responsabilități. Face parsare de date, actualizare de structuri interne, management de stream-uri de rețea, compunere de mesaje și trimitere de mesaje, compunere de răspunsuri.
- [x] typo: „Coulnd not”
- [ ] Too many things are included in the main of thermostat
- [x] What would it take to have the valve threads done in only one thread? How about doing it in the main thread?
- [x] remove la valve ar trebui sa se realizeze pe baza ip-ului


### Networking

- [x] GetStream ar trebui să returneze un stream, nu un int.
- [x] Porturile sunt uint16_t. Nu string, nu altceva.
- [x] `IsResponseASuccess` should be `Successful`

### Features

- [x] input validator pentru requesturi HTTP si IotDCP poate
- [ ] logger (single tone)
- [x] polling de la valve la thermostat -> daca nu mai raspunde termostatul atunci revenim la o valoare default ca target al valvelor
- [ ] unit teste
- [x] valva sa primeasca requesturi http ca sa stie care ii este thermostatul (? de discutat deoarece momentan se intampla invers)
- [x] nu ar trebui sa putem inregistra o valva daca nu e pornita
- [ ] folosire json pentru interpretari de request/response
- [x] folosire stl petru operatii de cautare/stergere etc
- [x] teste pentru GetIP si GetPort pentru NetworkStream si Request

### FIXES

- [ ] de ce trebuiesc adaugate iar pathurile in router la RouterTest.cpp
- [x] foloseste try catch pentru apelarea Request::GetPathVar, eventual o functie care sa faca try catchul
- [ ] repara testele pentru NetworkStream
- [x] daca o valva e deconectata de la un thermostat ar trebui sa se revina la o valoare default

### 2022-08-19
- [x] Excepțiile nu sunt prinse peste tot (de exemplu nu faci catch pe stoi).
- [x] Structura executabilelor ar trebui să fie: 1. Procesarea argc/argv într-o funcție și pus informațiile din parametri într-o structură, să zicem CommandLineParameters 2. apelată o funcție care folosește acei parametri.
- [x] `int main` trebuie să returneze ceva.
- [ ] La teste nu adăuga verificarea pe textul excepției, pentru că va trebui să modifici excepția mai încolo, și poate vei vrea să nu ai o tonă de teste de întreținut. Verifică tipul excepției, totuși.
- [ ] Testele tale în general verifică doar situațiile favorabile - dar ar trebui să creeze și să verifice comportamentul mai ales în situațiile în care informațiile sunt greșite sau la limită

Thermostat
    - [x] Posibilitatea sa imi aleg eu on interfata, nu doar eth0?
    - [x] typo 'successfuly' -> 'successfully'
    - [x] Ce se intampla daca vreau sa adaug/sterg o valva folosind server_name si port de la thermostat?
    - [x] /remove_valve returneaza doar 'failed to write'  daca valva pe care incerc sa o sterg nu a fost conectata anterior.
      Poate un mesaj cu 'unable to disconnect. Valve not found' ar fi mai util
    - [x] Ping-ul ar trebui sa fie pentru verificarea conexiunii cu valvele sau ...?

Valve
    - [x] Posibilitatea sa imi aleg eu on interfata, nu doar eth0?
    - /set_target nu functioneaza cum trebuie
    - /connect si /disconnect imi dau exceptii

System
    - [x] poate ar trebui sa avem doar o lista cu comenzile pe care le folosim si sa nu dam posibilitatea sa poata fi folosite comenzi nedorite?

Test
    - 2 teste care imi dau fail
    - de adaugat teste cu conexiuni intre valve si thermostate (diferite scenarii)


### Review scenarii

- [ ] valoarea predefinita trebuie folosita la pronirea independenta de termostat si atat, chiar daca termostatul se deconecteaza
- [ ] fisier de configurare pentru valva si termostat, in care sa stocam valoarea predefinita + valvele/termostatul asociat(e)
- [ ] friendly name pentru valve + afisarea numelor valvelor care nu au putut fi actualizate
- [ ] simualre camera care se raceste singura, odata ajunsa la 1-2 grade sub pragul tinta incepem incalzirea
