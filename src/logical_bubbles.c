#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

/**
 * PROTOTIPO: Logical Bubble Machine (LBM) v1.0
 * 
 * Concetto di Pietro Ruà: 
 * Far lavorare i 64 bit non come un numero, ma come un esercito di 64 
 * agenti indipendenti ("Bolle") che collaborano tra loro.
 * 
 * In questo esempio:
 * - Ogni bit ha un ruolo (Sentinella, Soldato, Allarme).
 * - Una regola di "Evoluzione" trasmette l'informazione tra i bit 
 *   in modo ultra-rapido usando solo logica bitwise.
 */

// Ruoli Bit (Esempi)
#define BIT_SENTINELLA (1ULL << 0)  // Il bit 0 sorveglia
#define BIT_ALLARME    (1ULL << 63) // Il bit 63 segnala l'allarme globale
#define MASCHERA_SOLDI (0x7FFFFFFFFFFFFFFEULL) // Gli altri sono l'esercito

// Regola di Evoluzione:
// Se la Sentinella rileva qualcosa (1), l'allarme deve propagarsi 
// istantaneamente attraverso l'esercito verso il bit 63.
uint64_t tick_evoluzione(uint64_t stato) {
    if (stato & BIT_SENTINELLA) {
        // La sentinella è attiva: propaga il segnale a tutto l'esercito
        // Invece di un ciclo 'for', usiamo la forza del processore
        return stato | MASCHERA_SOLDI | BIT_ALLARME;
    }
    return stato & ~BIT_ALLARME; // Tutto tranquillo
}

void mostra_esercito(uint64_t stato) {
    printf("Stato: [");
    for (int i = 63; i >= 0; i--) {
        printf("%c", (stato & (1ULL << i)) ? '1' : '.');
    }
    printf("]\n");
}

int main() {
    uint64_t esercito = 0;

    printf("--- Logical Bubble Machine ---\n");
    printf("Inizializzazione esercito (tutto tranquillo)...\n");
    mostra_esercito(esercito);

    printf("\nPassaggio 1: La Sentinella (Bit 0) rileva un'intrusione!\n");
    esercito |= BIT_SENTINELLA;
    mostra_esercito(esercito);

    printf("\nPassaggio 2: Singolo Battito di Clock (Evoluzione)...\n");
    esercito = tick_evoluzione(esercito);
    mostra_esercito(esercito);

    if (esercito & BIT_ALLARME) {
        printf("\n>>> RISULTATO: L'esercito ha reagito all'unisono!\n");
        printf(">>> L'allarme (Bit 63) e' attivo grazie alla collaborazione esterna.\n");
    }

    return 0;
}
