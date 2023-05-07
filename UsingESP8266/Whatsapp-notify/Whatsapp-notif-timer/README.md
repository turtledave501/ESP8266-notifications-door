# Notifikace přes WhatsApp s časovačem

Tento kód slouží jako monitor dveří, který zasílá upozornění na změnu stavu dveří pomocí CallMeBot WhatsApp API. 

## Použité technologie

Kód byl napsán v jazyce C++ a používá následující knihovny:
- ESP8266WiFi
- ESP8266HTTPClient
- WiFiClient
- UrlEncode

## Základní nastavení

Pro základní nastavení programu je nutné provést následující kroky:

- Stáhněte a nastavte[Arduino IDE](https://www.arduino.cc/en/software).
- Připojte ESP8266 k počítači pomocí USB kabelu.
- Otevřete program WhatsApp-notify.ino v Arduino IDE.
- Vyplňte proměnné `Wifi_Name` a `Wifi_Password` s názvem a heslem vaší WiFi sítě.
- Vyplňte proměnné `phone_num` a `API` s telefonním číslem a API klíčem pro `CallMeBot API`.
- Připojte spínač k pinu 4 a LED diodu k pinu 2 na vašem ESP8266.
- (Volitelné) nastavit dobu časovače v proměnné `timerDuration`, základní je 3 minuty nebo 180000 milisekund
- Program nahrajte na ESP8266.
*[jak spustit `CallMeBot`](https://www.callmebot.com/blog/free-api-whatsapp-messages/)*

## Popis 

Kód se spustí připojením k WiFi, na které jsou definovány přihlašovací údaje v proměnných `Wifi_Name` a `Wifi_Password`. Pokud se zařízení úspěšně připojí k WiFi, zapne se LED na desce, která ukazuje aktuální stav dveří. 

Kód obsahuje funkci `changeDoorStatus`, která je spuštěna při změně stavu reedového spínače připojeného na pin `reedSwitch` na desce. Pokud je reedový spínač aktivován, časovač se spustí a kód odešle zprávu otevření dveří přes WhatsApp API s použitím funkce `sendMessage`.

Pokud jsou dveře otevřeny déle než tři minuty, odešle kód upozornění "Door still open!".

## Knihovny
Program používá následující knihovny:
- `ESP8266WiFi.h`: Knihovna pro připojení k WiFi sítím s deseti funkcemi pro kontrolu stavu spojení.
- `ESP8266HTTPClient.h`: Knihovna pro ovládání HTTP klienta pro přenos dat.
- `WiFiClient.h`: Knihovna pro připojení k serveru přes TCP/IP protokol.
- `UrlEncode.h`: Knihovna pro kódování URL řetězců.

## Funkce

### sendMessage()
Tato funkce slouží k odeslání zprávy na zadané telefonní číslo pomocí API od Callmebot. Využívá k tomu HTTP POST požadavek s určitými parametry. Pokud odeslání zprávy selže, funkce opakovaně pošle požadavek až do maxima tří pokusů.

### setup()
Tato funkce provádí inicializaci zařízení a sítě. Nastavuje WiFi spojení a reedspínač, na kterém je připojen dveřní senzor. Dále připojuje funkci changeDoorStatus() jako obsluhu přerušení a nastavuje LED podle aktuálního stavu dveří.

### loop()
Hlavní funkce programu, která se neustále opakuje a kontroluje aktuální stav dveří. Pokud dojde ke změně, aktualizuje LED a odesílá zprávu s novým stavem. Pokud jsou dveře otevřené déle než 3 minuty, funkce odesílá notifikaci

## Omezení programu

Program může být omezen tím, že reedové spínače nejsou dostatečně přesné a mohou detekovat nesprávný stav dveří. To může vést k odeslání chybných notifikací.

Je také nutné mít aktivní WiFi připojení, aby program mohl odesílat informace.

## Další možnosti vylepšení

Program lze dále vylepšit a upravit tak, aby lépe vyhovoval potřebám uživatele. Například:

- Přidání dalších vstupů pro monitorování dalších částí garáže, například teploty.
- Přidání možnosti nastavení intervalu mezi odesláním stavu dveří na WhatsApp.
- Přidání dalších akcí k vykonání při změně stavu dveří, například zapnutí světel.

## Závěr

Tento program umožňuje monitorování stavu dveří a odesílání notifikací za pomocí služby CallMeBot služby a WhatsApp. Program má také funkci časovače, která uživatele znovu upozorní pokud jsou dveře stále otevřené po 3 minutách Program je poměrně jednoduchý, ale může být dále upraven a vylepšen podle potřeb uživatele.