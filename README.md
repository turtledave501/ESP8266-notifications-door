# Dokumentace o práci a využití ESP8266.

## očekávaná náročnost

Projekt nebude moc složitý, program by měl být relativně jednoduchý, ale můžou se vyskytnout problémy se znalostmi C++, arduinem a nejspíš budu muset trochu pájet. Implementace IFTTT vypadá jednoduše. Dále využít jiné externí zdroje pro posílaní notifikací nemusí být náročné.

## Použité zdroje

U projektů využívám ESP8266 modul pro připojení k WiFi a zpracovaní programů, dále využívám magnetický spínač MC-38.

## Základní nastavení
U všech programů bude potřeba nastavit následující věci `Wifi_Name = Jméno vaší Wifi sítě` `Wifi_Password = Heslo vaší sítě`, další věci k nastavení najdete u jednotlivých programů v jejich složce.

## K čemu projekty slouží?

Zatím oba projekty jsou určeny k monitorování stavu dveří a následné odeslání notifikace pokud se stav změní. Způsob notifikací je zatím jen `Email` a `WhatsApp`

## Nadcházející updaty

Implementace času, kde program pošle notifikaci až po nějaké době a napíše že jste zapomněli zavřít dveře
