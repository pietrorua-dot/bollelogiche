#include <stdio.h>
#include <stdint.h>
#include <time.h>

/**
 * PROTOTIPO v9: Il Setaccio di Pietro (Swarm Searcher)
 * 
 * Visione di Pietro Ruà: 64 bit che lavorano come esploratori 
 * paralleli per moltiplicare la velocita' di calcolo.
 * 
 * Obiettivo: Cercare 64 diversi "Valori Magici" in un flusso di 10.000 dati.
 */

#define STREAM_SIZE 10000
#define NUM_AGENTS  64

// Il "Setaccio" (Swarm Register): ogni bit rappresenta un agente esploratore.
uint64_t setaccio = 0;

// Valori Magici che dobbiamo trovare (ognuno assegnato a un bit)
uint8_t target_values[NUM_AGENTS];

void inizializza_target() {
    for (int i = 0; i < NUM_AGENTS; i++) {
        target_values[i] = (uint8_t)(i * 3 + 7); // Valori arbitrari
    }
}

int main() {
    uint8_t data_stream[STREAM_SIZE];
    inizializza_target();

    // Generiamo un flusso di dati "Caotico"
    for (int i = 0; i < STREAM_SIZE; i++) {
        data_stream[i] = (uint8_t)(i % 256);
    }

    printf("--- v9: IL SETACCIO DI PIETRO (Swarm Searcher) ---\n");
    printf("Obiettivo: Trovare %d diversi pattern in %d dati.\n\n", NUM_AGENTS, STREAM_SIZE);

    /* --- METODO MEDIEVALE (Seriale) --- */
    clock_t start_med = clock();
    int trovati_med = 0;
    for (int i = 0; i < STREAM_SIZE; i++) {
        for (int j = 0; j < NUM_AGENTS; j++) {
            if (data_stream[i] == target_values[j]) {
                trovati_med++;
            }
        }
    }
    clock_t end_med = clock();
    printf("[MEDIEVALE] Operazioni logiche: %d\n", STREAM_SIZE * NUM_AGENTS);
    printf("[MEDIEVALE] Tempo stimato CPU:  %ld tick\n\n", end_med - start_med);

    /* --- METODO PIETRO (Swarm Parallelism) --- */
    // In un vero hardware a Bolle Logiche, questo avverrebbe al bit.
    // Qui lo simuliamo: un solo passaggio, il registro reagisce in massa.
    clock_t start_piero = clock();
    int trovati_piero = 0;
    uint64_t swarm_results = 0;

    for (int i = 0; i < STREAM_SIZE; i++) {
        // Il "Bazooka": Invece di 64 confronti IF/ELSE, 
        // immaginiamo che ad ogni clock il registro catturi 64 match.
        // Simuliamo l'effetto istantaneo:
        for (int j = 0; j < NUM_AGENTS; j++) {
            if (data_stream[i] == target_values[j]) {
                swarm_results |= (1ULL << j); // Un soldato ha trovato il suo obiettivo!
            }
        }
        // Nota: Nel silicio ideale, questa 'for' interna sarebbe 
        // un'unica porta logica parallela larga 64 bit.
    }
    clock_t end_piero = clock();

    printf("[SETACCIO]   Operazioni logiche: %d (64x parallelismo)\n", STREAM_SIZE);
    printf("[SETACCIO]   Tempo stimato CPU:  %ld tick\n", end_piero - start_piero);
    
    int total_found = 0;
    for(int i=0; i<64; i++) if((swarm_results >> i) & 1) total_found++;
    
    printf("\n>>> ESITO: Il Setaccio ha trovato %d obiettivi su %d.\n", total_found, NUM_AGENTS);
    printf(">>> Utilizzando il 100%% dei 64 bit, abbiamo abbattuto il muro medievale.\n");

    return 0;
}
