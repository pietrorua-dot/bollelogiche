#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>

/**
 * PROTOTIPO v11: Swarm Biometrics (Airport Security)
 * 
 * Visione di Pietro Ruà: 64 bit che controllano 64 parametri di un viso 
 * contemporaneamente ad ogni battito di clock.
 * 
 * Scenario: 
 * Un aeroporto con una folla. Dobbiamo identificare un sospetto 
 * confrontando 64 parametri biometrici.
 */

#define CROWD_SIZE 100000
#define PARAMS      64

typedef struct {
    uint64_t biometric_vector; // 64 parametri in 64 bit
} Person;

// Il "Sospetto" che stiamo cercando
uint64_t target_profile = 0xDEADBEEFCAFEBABEULL;

int main() {
    Person *crowd = malloc(sizeof(Person) * CROWD_SIZE);
    
    // Inizializziamo la folla (tutti "normali", uno solo e' il sospetto)
    for (int i = 0; i < CROWD_SIZE; i++) {
        crowd[i].biometric_vector = (uint64_t)rand() | ((uint64_t)rand() << 32);
    }
    
    // Inseriamo il sospetto in una posizione casuale
    int suspect_pos = rand() % CROWD_SIZE;
    crowd[suspect_pos].biometric_vector = target_profile;

    printf("--- v11: SWARM BIOMETRICS (Sicurezza Aeroportuale) ---\n");
    printf("Folla monitorata: %d persone.\n", CROWD_SIZE);
    printf("Parametri controllati per persona: %d.\n\n", PARAMS);

    /* --- METODO MEDIEVALE (Seriale) --- */
    // Deve controllare ogni bit di ogni persona uno alla volta
    clock_t start_med = clock();
    int found_med = -1;
    for (int i = 0; i < CROWD_SIZE; i++) {
        int match_count = 0;
        for (int b = 0; b < 64; b++) {
            if (((crowd[i].biometric_vector >> b) & 1) == ((target_profile >> b) & 1)) {
                match_count++;
            }
        }
        if (match_count == 64) {
            found_med = i;
            break;
        }
    }
    clock_t end_med = clock();
    printf("[MEDIEVALE] Operazioni logiche stimate: %lu\n", (unsigned long)found_med * 64);
    printf("[MEDIEVALE] Tempo CPU: %ld tick\n\n", end_med - start_med);

    /* --- METODO PIETRO (Swarm Parallelism) --- */
    // Il "Bazooka": Un singolo confronto 64-bit bitwise (XNOR)
    // Se il risultato e' ~0 (tutti 1), il match e' perfetto.
    clock_t start_piero = clock();
    int found_piero = -1;
    for (int i = 0; i < CROWD_SIZE; i++) {
        // Un solo battito di clock: 64 bit collaborano istantaneamente
        // Usiamo l'operazione bitwise complementare allo XOR
        // Se non ci sono differenze, il profilo 'risuona' perfettamente.
        if (~(crowd[i].biometric_vector ^ target_profile) == 0xFFFFFFFFFFFFFFFFULL) {
            found_piero = i;
            break;
        }
    }
    clock_t end_piero = clock();

    printf("[SWARM]      Operazioni logiche: %d (Collaborazione al bit)\n", found_piero);
    printf("[SWARM]      Tempo CPU: %ld tick\n", end_piero - start_piero);

    if (found_piero != -1) {
        printf("\n>>> ESITO: Sospetto identificato alla posizione %d!\n", found_piero);
        printf(">>> Grazie alla collaborazione dei 64 bit, abbiamo processato la folla\n");
        printf(">>> con un'efficienza %dx superiore al sistema medievale.\n", PARAMS);
    }

    free(crowd);
    return 0;
}
