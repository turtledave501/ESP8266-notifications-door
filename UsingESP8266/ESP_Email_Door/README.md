# Notifikace přes email

## Popis programu

Tento program byl vytvořen pro monitorování stavu garážových dveří. Využívá přitom reedových kontaktů, které snímají, zda jsou dveře otevřeny nebo zavřeny. Pokud se stav dveří změní, program odesílá informaci o této události na předem definovaný webhook v IFTTT. Tím je umožněno například odeslání notifikace, emailu nebo spuštění jiné akce.

Program je napsán v jazyce C++ pro platformu ESP8266, využívá knihovnu ESP8266WiFi.h a byl testován na desce NodeMCU v2.

Program je rozdělen do několika funkcí:

## Základní nastavení

Pro základní nastavení programu je nutné provést následující kroky:

- Stáhněte a nainstalujte Arduino IDE.
- Připojte ESP8266 k počítači pomocí USB kabelu.
- Otevřete program ESP_Email_Door.ino v Arduino IDE.
- Zkontrolujte, zda jsou v kódu správně nastaveny připojovací údaje k WiFi a API klíč od služby IFTTT. Údaje se nachází v následujícím bloku kódu:
- Dále je nutné přizpůsobit název webhooku (door_status) ve webové adrese:
- Vyberte správnou desku a sériový port v Arduino IDE.
- Nahrát program na desku pomocí tlačítka "Upload".
- Po nahrání programu by se deska měla připojit k WiFi síti a začít odesílat informace o stavu dveří na IFTTT.

## Funkce
### `setup()`

- Funkce inicializuje vstupy a výstupy na ESP8266.
- Nastavuje přerušení na reedových kontaktech.
- Připojuje desku k WiFi síti.

### `loop()`

- Funkce průběžně kontroluje, zda se změnil stav dveří.
- Pokud došlo ke změně, program počká 500 ms (aby se nestalo, že se stav dveří změní několikrát za sebou) a odešle informaci o stavu dveří na IFTTT.

### `changeDoorStatus()`

- Funkce nastavuje globální proměnnou `doorStatus` na `true`, pokud došlo ke změně stavu dveří.

## Implementace

Program začíná s definováním proměnných pro reedový kontakt a LED diodu, která signalizuje stav dveří. Proměnná `doorStatus` uchovává informaci o tom, zda došlo ke změně stavu dveří, `state` uchovává aktuální stav dveří a `doorState` uchovává textový popis tohoto stavu. Dále je definován interval, který určuje, jak dlouho program počká, než opět odešle informaci o stavu dveří.

Následuje inicializace WiFi a připojení k síti. V `setup()` také dochází k nastavení přerušení na reedových kontaktech. To umožňuje, aby program okamžitě zareagoval na změnu stavu dveří.

V `loop()` funkci se průběžně kontroluje stav dveří. Pokud došlo ke změně, program počká stanovený interval a následně odešle informaci íme v dokumentaci...

## Zapojení

Pro správné fungování programu je nutné správně zapojit ESP8266 a reedové spínače.

ESP8266 musí být napájeno z externího zdroje, například 5V napájení z USB portu. Reedové spínače jsou zapojeny na digitální vstup 4 desky ESP8266.

Pokud použijete jiný vstup, bude nutné aktualizovat programový kód tak, aby odpovídal použitým vstupům.

## Omezení programu

Program může být omezen tím, že reedové spínače nejsou dostatečně přesné a mohou detekovat nesprávný stav dveří. To může vést k odeslání chybných notifikací.

Je také nutné mít aktivní WiFi připojení, aby program mohl odeslat informaci na IFTTT.

## Další možnosti vylepšení

Program lze dále vylepšit a upravit tak, aby lépe vyhovoval potřebám uživatele. Například:

- Přidání dalších vstupů pro monitorování dalších částí garáže, například teploty.
- Přidání možnosti nastavení intervalu mezi odesláním stavu dveří na IFTTT.
- Přidání dalších akcí k vykonání při změně stavu dveří, například zapnutí světel.

## Závěr

Tento program umožňuje monitorování stavu dveří a odesílání notifikací, emailů a spouštění jiných akcí pomocí služby IFTTT. Program je poměrně jednoduchý, ale může být dále upraven a vylepšen podle potřeb uživatele.
