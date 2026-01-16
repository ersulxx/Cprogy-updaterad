Instruktion för att bygga och testa: 

För att bygga projektet krävs en C++ kompilator samt att biblioteket SDL3 är installerat på systemet. Koden kan kompileras med make kommandot i projektets rotmapp. Detta kommer att kompilera källkoden. När bygget är klart startas spelet med kommandot ./build/debug/play 
För att spelet ska fungera korrekt måste biblioteket SDL3 vara installerade. Spelet hämtar sina visuella och textbaserade resurser från följande relativa sökvägar(se också Constants.h)

Bilder: resources/images (Innehåller bakgrund, rymdskeppet, kula och fiender)

Typsnitt: resources/font (Innehåller .tff fil för texter)

Konstanter: include/Constants.h Samtliga filnamn och grundinställningar finns centraliserade i Constants.h.
För testning verifieras att rymdskeppet kan styras med piltangenterna och att fiender spawnas korrekt. Testa även att GameOver-rutan dyker upp om en fiende når botten. 
Tryck på uppåt piltangenten för att skjuta fiender för att verifiera att en kula skapas och att fienden försvinner när de träffas. Se också till att poängräknaren(uppe till höger sida av skärmen) uppdateras vid varje träff. 
