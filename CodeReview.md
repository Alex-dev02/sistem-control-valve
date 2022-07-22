# Code review

## 2022-07-22

### Code structure

- [ ] rename pe executabile sa-thermostat, sa-valve
- [ ] de vreme ce ai folosit directoare separate fă biblioteci separate pentru fiecare folder (networking)
- [ ] folosește Include paths (vezi de exemplu acest [item din SO](https://stackoverflow.com/questions/13703647/how-to-properly-add-include-directories-with-cmake)).
- [ ] folosește naming consecvent pentru fișiere. Litere mici, și pentru fișiere și pentru directoare.
- [ ] include doar ce e necesar. Include minimul necesar în headere - include doar ce ai nevoie în fiecare unitate de compilare.

### Valve/Thermostat

- [ ] `void SetTemperature(float temperature);` și `void IncrementTemperature();` sunt publice. De ce?
- [ ] Îmi e neclară relația dintre clasa Valve și clasa Router. Valva este un Router? Are un router? Ar trebui să fie derivată din Router?
- [ ] Pentru Router este un tip de date complex ar trebui să nu poată fi copiat - operațiunea de copiere nu ar trebui să aibă sens pentru Router. Tu faci o copie în main, dar dacă adaug on-the-fly noi endpoints în Router? `main` nu le va vedea.
- [ ] main-ul de la termostat și valvă seamănă foarte mult. Se poate refolosi acel cod?
- [ ] Thermostat::SetTarget are prea multe responsabilități. Face parsare de date, actualizare de structuri interne, management de stream-uri de rețea, compunere de mesaje și trimitere de mesaje, compunere de răspunsuri.
- [ ] typo: „Coulnd not”

### Networking

- [ ] GetStream ar trebui să returneze un stream, nu un int.
- [ ] Porturile sunt uint16_t. Nu string, nu altceva.
- [ ] `IsResponseASuccess` should be `Successful`
