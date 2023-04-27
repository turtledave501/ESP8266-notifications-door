# Notifikace přes email

## Popis programu

Program monitoruje stav dveří pomocí reedů. Pokud se stav dveří změní, odesílá program informaci o tomto stavu na předem definovaný webhook v IFTTT. Tím se umožní například odeslání notifikace, emailu nebo spuštění jiné akce.

Program je rozdělen do několika funkcí:

### `setup()`

- Funkce inicializuje vstupy a výstupy na ESP8266.
- Nastavuje přerušení na reedových kontaktech.
- Připojuje desku k WiFi síti.

### `loop()`

- Funkce průběžně kontroluje, zda se změnil stav dveří.
- Pokud došlo ke změně, program počká 1500 ms (aby se nestalo, že se stav dveří změní několikrát za sebou) a odešle informaci o stavu dveří na IFTTT.

### `changeDoorStatus()`

- Funkce nastavuje globální proměnnou `doorStatus` na `true`, pokud došlo ke změně stavu dveří.

Program také obsahuje část kódu, která není momentálně použita (výpis výše), ale mohla by být použita pro načítání připojovacích údajů z textového souboru.

## Použití

Před použitím programu je nutné zadat připojovací údaje k WiFi a API klíč od služby IFTTT do příslušných proměnných v kodu **Garage_Door.ino** (`ssid`, `password`, `apiKey`). Dále je nutné přizpůsobit název webhooku (`door_status`) a názvy parametrů (`value1` atd.) dle potřeby.

Program se nahrává na desku ESP8266 a spouští se při zapnutí desky. Pokud dojde ke změně stavu dveří, program odešle informaci na IFTTT, to aktivuje webhook a pošle email na zadanou adresu.

*[Detailnější instrukce](https://randomnerdtutorials.com/door-status-monitor-using-the-esp8266/)*
