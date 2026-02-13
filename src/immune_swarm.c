#include <stdio.h>
#include <stdint.h>

/**
 * PROTOTIPO v8.1: Swarm Self-Healing (Bolle Tripe)
 * 
 * Visione di Pietro Ruà: 64 bit che lavorano come un esercito di bolle.
 * 
 * In questo modello:
 * - Dividiamo i 64 bit in 21 "Bolle Logiche" (3 bit ciascuna).
 * - Ogni bolla porta 1 bit di informazione reale in tripla copia.
 * - Se un bit viene alterato, la bolla "vota" e ripristina la verita'.
 * - Tutto avviene istantaneamente (simulazione di un solo clock).
 */

typedef struct {
    uint64_t registro;
} SwarmRegister;

// Regola di Evoluzione: Ogni bolla di 3 bit applica un voto di maggioranza
uint64_t tick_guarigione(uint64_t r) {
    uint64_t risultato = 0;
    for (int i = 0; i < 21; i++) {
        int offset = i * 3;
        int b1 = (r >> (offset)) & 1;
        int b2 = (r >> (offset + 1)) & 1;
        int b3 = (r >> (offset + 2)) & 1;
        
        // Maggioranza (Consenso della Bolla)
        int voto = (b1 + b2 + b3 >= 2) ? 1 : 0;
        
        // Rispristina la bolla sana
        if (voto) {
            risultato |= (7ULL << offset);
        }
    }
    return risultato;
}

void mostra_bolle(uint64_t r) {
    for (int i = 20; i >= 0; i--) {
        int offset = i * 3;
        int b1 = (r >> offset) & 1;
        int b2 = (r >> (offset+1)) & 1;
        int b3 = (r >> (offset+2)) & 1;
        printf("[%d%d%d] ", b3, b2, b1);
    }
    printf("\n");
}

int main() {
    // 1. Stato Sano: Ogni bolla ha 3 bit uguali (consistenza)
    uint64_t swarm = 0xDB6DB6DB6DB6DB6DULL; // Pattern 110 alternato in bolle
    
    printf("--- v8.1: ESERCITO DI BOLLE LOGICHE (Self-Healing) ---\n");
    printf("Esercito Sano:    "); mostra_bolle(swarm);

    // 2. Attacco: L'hacker colpisce 3 bit in bolle diverse
    printf("\nATTACCO! L'hacker colpisce i bit 5, 31 e 61...\n");
    swarm ^= (1ULL << 5);  // Colpisce bolla 1
    swarm ^= (1ULL << 31); // Colpisce bolla 10
    swarm ^= (1ULL << 61); // Colpisce bolla 20
    printf("Esercito Infetto: "); mostra_bolle(swarm);

    // 3. Reazione: Battito di clock
    printf("\nBattito di clock (Collaborazione istantanea)...\n");
    uint64_t swarm_curato = tick_guarigione(swarm);
    
    printf("Esercito Curato:  "); mostra_bolle(swarm_curato);

    if (swarm_curato == 0xDB6DB6DB6DB6DB6DULL) {
        printf("\n>>> ESITO: Il bazooka di Pietro ha vinto!\n");
        printf(">>> 21 bolle hanno collaborato per eliminare le infiltrazioni.\n");
        printf(">>> L'informazione e' rimasta integra grazie al consenso al bit.\n");
    }

    return 0;
}
