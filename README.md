# Dokumentace o práci a využití ESP8266.

## Očekávaná náročnost

Projekt nebude moc složitý, programy by měli být relativně jednoduché, ale můžou se vyskytnout problémy se znalostmi C++, arduinem a nejspíš budu muset trochu pájet. Implementace IFTTT vypadá jednoduše. Dále využití jiných zdrojů pro posílaní notifikací nemusí být náročné.

## Použité zdroje

U projektů využívám ESP8266 modul pro připojení k WiFi a zpracovaní programů, dále využívám magnetický spínač MC-38. 
Program je v C++ a programuji v Arduino IDE.

## Základní nastavení
- U všech programů bude potřeba nastavit následující věci `Wifi_Name` = `Jméno vaší Wifi sítě` `Wifi_Password` = `Heslo vaší sítě`, další věci k nastavení najdete u jednotlivých programů v jejich složce.
- Stáhněte a nastavte [Arduino IDE](https://www.arduino.cc/en/software).

## Nastavení ESP8266 a spínače

Připojte spínač k 3V3 outputu na jeden konec spínače a na druhý připojte na D2 pin na ESP, dále přes rezistor (rezistor je tam z toho důvodu, aby omezil falešná data z spínače) napojte na GND pin.
<img src="https://user-images.githubusercontent.com/57016791/236673916-4ff3f848-99bd-4916-bdae-a8b51a4646a9.jpg" alt="image description" width="517"/> ![image](https://user-images.githubusercontent.com/57016791/236674840-cc1ec4c7-9554-4b1c-ae75-a66e7bbfd7fd.png)

## K čemu projekty slouží?

Zatím oba projekty jsou určeny k monitorování stavu dveří a následné odeslání notifikace pokud se stav změní. Způsob notifikací je zatím jen `Email` a `WhatsApp`

## Nadcházející updaty

- [x]  Implementace času, kde program pošle notifikaci až po nějaké době a napíše že jste zapomněli zavřít dveře
- [ ]  Implementovat jiné služby
- [ ]  Zjednodušit použití, úprava WiFi údajů mimo .ino 
