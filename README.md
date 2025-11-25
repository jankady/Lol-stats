
<p align="center"><h1 align="center">LOL-STATS</h1></p>

Jednoduchý nástroj pro zobrazování statistik z League of Legends.

## Struktura projektu

```
└── Lol-stats/
    ├── CMakeLists.txt
    ├── header
    │   ├── display_html.h
    │   ├── league_player.h
    │   ├── stats.h
    │   └── utility.h
    ├── main.c
    ├── src
    │   ├── display_html.c
    │   ├── league_player.c
    │   ├── stats.c
    │   └── utility.c
    └── test-data
        ├── data_200.txt
        ├── data_400.txt
        ├── matches.in
        ├── player_names.in
        └── result.html
```
## Funkcionalita

Tento projekt slouží k načtení statistik z textových souborů a následně vygenerování HTML stránky s těmito statistikami.
* **Data:** Ve složce test-data, jsou příklady testovacích dat.
* **Funkce:** Program potřebuji 3 parametry:
  1. Cesta k souboru odehraných zápasů zápasu (test-data/matches.in)
  2. Cesta k souboru s ID a jménem hráčů (test-data/player_names.in)
  3. Cesta kde bude vytvořena stránka ze statiskami (test-data/result.html)
* **Výstup:** Vygenerovaná HTML stránka obsahuje:
   * Aktuální rank a ELO.
   * Winrate a počet her.
   * KDA
   * počet výher a za jaký tým

## Jak spustit

Pro spuštění si stáhněte repozitář k sobě na disk.

### Instalace a Build

1.  **Klonování repozitáře:**
    ```bash
    git clone https://github.com/jankady/Lol-stats.git
    cd Lol-stats
    ```

2.  **Vytvoření build adresáře:**
    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```
    
3.  **Spuštění:**
    ```bash
    ./lol_stats ../test-data/matches.in ../test-data/player_names.in ../test-data/result.html
    ```

---
*Vytvořil Jan Kaduch*