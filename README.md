# DND

## Probleemstelling

Ik gebruik vrij vaak de [Pomodore](http://pomodorotechnique.com/) techniek om me te focussen op mijn werk. Bij Pomodore is het de bedoeling dat je gedurende 25 minuten focust op 1 bepaalde taak, zonder deze te onderbreken. Nadeel is dat het voor je collega's niet altijd duidelijk is dat je in deze 25 minuten niet gestoord mag worden.

## Oplossing

Een klein toestelletje dat je op je bureau kan plaatsen dat aangeeft dat je voor x-aantal minuten niet gestoord mag worden.

* * *

## Technologie keuze

### Beperkingen
* Klein zodat het kan in gebouwd worden en een behuizing die op een monitor kan geklemd of geplaatst worden.
* Internet geconnecteerd om Pomodore te staren en voor toekomstige uitbreidingen.
* 2 display's
> 1. duidelijke aanduiding in minuten voor collega's
> 2. grafische en niet storende aanduiding voor mij
* auditief (maar niet storend) signaal bij einde van de Pomodore

### Hardware
* controller: Spark Core van [spark.io](http://docs.spark.io/hardware/)
* display's: 
** 7-segment met I2C backpack van [Adafruit](http://www.adafruit.com/products/1002)
** 8x8 LED Matrix met I2C backup van [Adafruit](http://www.adafruit.com/products/1050)
* Piezoelectric buzzer

#### Spark
De Spark Core is een ontwikkelingsplatform met Wifi en is code-compatible met Arduino. Dit heeft als voordeel dat je bestaande Arduino code kan gebruiken.
Om de firmware op de Spark Core te uploaden kan je dit op ofwel via de browser doen via een online editor of gebruik maken van commandline tools. Ik heb gebruik gemaakt van de online editor voor deze fase in ontwikkeling om zo snel mogelijk in de code te duiken zonder het installeren van drivers of software. Later heb ik wel om het debuggen wat makkelijker te maken gewerkt met de [Spark Monitor](https://github.com/spark/spark-cli) in terminal.

* * * 

## Ontwikkeling: Core en de componenten aansluiten.

1. spark op breadboard plaatsen
2. connecteer A0 en GND op de pinnen van de piezo buzzer
3. verbind de 3V3 met de positieve (+) pinnen van de matrix en het 7-segment display
4. verbind de GND met de negatieve (-) pinnen van de matrix en het 7-segment display
5. verbind D1 met clock (C) pinnen van de matrix en het 7-segment display
6. verbind D0 met de data (d) pinnen van de matrix en het 7-segment display

* * *

## Ontwikkeling: Firmware

### Stap 1: Hello World
Als eerste kennismaking met de Spark Core begon ik met de "hello world" van de electronica, een LED laten branden door middel van  een curl commando (in plaats van een drukknopje).

Je kan de code hier bekijken. **TODO! github link**

#### Licht aan
_POST /v1/devices/{DEVICE_ID}/{FUNCTION}_
**curl https://api.spark.io/v1/devices/{DEVICE_ID}/helloWorld -d access_token={TOKEN}**
#### Licht uit
**curl https://api.spark.io/v1/devices/{DEVICE_ID}/goodbyeWorld -d access_token={TOKEN}**

### Stap 2: Hello 7-segment
Adafruit heeft voor zijn LED I2C backpacks een Arduino Library voorzien een aantal van deze libraries kan je ook al terugvinden  in de Libraries sectie van de Spark.io online editor. Om een LED I2C backpack aan te sturen heb je twee libraries nodig.

1. ADAFRUIT_GFX: terug te vinden in de Spark.io library
2. ADAFRUIT_LEDBackpack: op het moment van schrijven nog geen werkende versie in de Spark.io libraries terug te vinden.

Voeg de ADAFRUIT_GFX library toe via de Libraries knop.
Om de LEDBackpack library manueel toe te voegen maak je een nieuwe file aan in de editor en noemt deze Adafruit_LEDBackpack, je zal merken dat er twee files worden aangemaakt, Adafruit_LEDBackpack. en Adafruit_LEDBackpack.cpp. Van de [Github](TODO!) pagina kopieer je de inhoud van de .h en .ccp file naar de respectievelijke pagina's in de online editor. Ik heb een aantal functies verwijderd uit de originele Adafruit library die niet nodig waren voor dit project en die problemen gaven bij het compileren.

#### Stappen om 7-segment display aan te spreken:
1. initialiseer variabele globaal
2. connecter segment op het I2C address van het de backpack, standaard is dit 0x70.
3. stuur data naar segment (print)
4. refresh het display (writeDisplay)

### Stap 3: Hello 8x8 Matrix
Standaard zijn de verschillende LED I2C Backpacks op het zelfde hardware adres (0x70) ingesteld, omdat we de Matrix en het 7-segment display apart willen aansturen is het nodig om het hardware. Dit kan eenvoudig door op het backpack een jumper te solderen zodat het adres veranderd naar 0x71. Meer info vind je [hier](https://learn.adafruit.com/adafruit-led-backpack/changing-i2c-address).

#### Stappen om Matrix aan te spreken:
1. initialiseer variabele globaal
2. connecter segment op het I2C address van het de backpack, door het aanpassen van de adres jumper is dit 0x71.
3. stuur On naar pixel (drawPixel(x,y, LED_ON))
4. refresh het display (writeDisplay)

### Stap 4: Beep
Voor het biesje op het einde van de Pomodore maak ik gebruik van een simpele Piezoelectric Buzzer. Ik heb een tijdje zitten zoeken op welke manier je geluid kan produceren met dit couponnetje. Maar eigenlijk is het vrij simpel, door snel achter elkaar het voltage hoog en laag te zetten creëer je een geluidje.

### Stap 5: DND firmware
In bovenstaande stappen zitten eigenlijk alle belangrijke leerpunten, wil je de volledige code overlopen vind je deze op de github pagina.

Doormiddel van een curl call (via Alfred workflow) start de timer met aftellen. Op de matrix zie je visueel hoe ver je staat binnen de Pomodore.

* * *  

## Problemen tijdens het project
Tijdens de ontwikkeling ben ik een paar keer op het probleem gestoten dat de Spark.io niet werd geüpdate na het flashes van de Spark Core. Dit probleem kon ik oplossen door de core terug te flashen naar de fabriek instellingen. Dit kan door beide drukknopjes op de core in te drukken, het reset knopje los te laten en dan wanneer de led wit (niet geel) flikkert ook los te laten. De Core zal dan terug opstarten met de standaard Tinker app. Na het opnieuw instellen van de wifi credentials kan je de core dan opnieuw flashen.

Heb je een core van voor de zomer 2014 is het aan te raden om de **"[Deep update](https://github.com/spark/spark-cli)"** uit te voeren.
