/***********************************************************/
/*           Programación para mecatrónicos               */
/*  Nombre:    Bienderl Gonzalez                          */
/*  Matricula: 2024-1302                                  */
/*  Seccion:   Miercoles                                  */
/*  Practica:  Primer parcial                             */
/*  Fecha:     5/10/2026                                   */                       
/* Link Practica:                                         */
/***********************************************************/
 #include <stdio.h>
#include <stdlib.h>

int main() {
    int N, M;
    long long L, U;
    
    // Lectura de dimensiones y límites
    if (scanf("%d %d %lld %lld", &N, &M, &L, &U) != 4) {
        printf("ERROR\n");
        return 0;
    }
    
    // Validación de restricciones iniciales
    if (N < 1 || N > 30 || M < 1 || M > 30 || L < 0 || U < 0 || L > U || U > 1000) {
        printf("ERROR\n");
        return 0;
    }
    
    long long matriz[30][30];
    int i, j;
    
    // Lectura de la matriz con validación de elementos
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            if (scanf("%lld", &matriz[i][j]) != 1) {
                printf("ERROR\n");
                return 0;
            }
            if (matriz[i][j] < 0 || matriz[i][j] > 1000) {
                printf("ERROR\n");
                return 0;
            }
        }
    }
    // Arreglos para guardar los resultados por fila y columna
    int eventos_fila[30];
    long long impacto_fila[30];
    int racha_fila[30];
    int inicio_racha_fila[30];
    int eventos_columna[30];
    
    // Inicializar vectores de columnas en 0
    for (j = 0; j < M; j++) {
        eventos_columna[j] = 0;
    }
    
    // Procesamiento principal por cada fila
    for (i = 0; i < N; i++) {
        int eventos = 0;
        long long impacto_total = 0;
        int max_racha = 0;
        int mejor_inicio = 0;
        
        int racha_actual = 0;
        int inicio_actual = 0;
        int en_racha = 0; // 0 falso, 1 verdadero
        
        for (j = 0; j < M; j++) {
            if (j >= 1) {
                long long d = matriz[i][j] - matriz[i][j - 1];
                if (d < 0) {
                    d = -d; // Valor absoluto manual
                }
                
                if (d < L || d > U) {
                    eventos++;
                    long long impacto_evento = 0;
                    if (d < L) {
                        impacto_evento = L - d;
                    } else {
                        impacto_evento = d - U;
                    }
                    impacto_total += impacto_evento;
                    eventos_columna[j]++;
                    
                    if (en_racha == 0) {
                        en_racha = 1;
                        inicio_actual = j + 1; // Índice base 1
                    }
                    racha_actual++;
                } else {
                    en_racha = 0;
                    racha_actual = 0;
                }
            } else {
                en_racha = 0;
                racha_actual = 0;
            }
            
            if (racha_actual > max_racha) {
                max_racha = racha_actual;
                mejor_inicio = inicio_actual;
            }
        }
        
        eventos_fila[i] = eventos;
        impacto_fila[i] = impacto_total;
        racha_fila[i] = max_racha;
        if (max_racha > 0) {
            inicio_racha_fila[i] = mejor_inicio;
        } else {
            inicio_racha_fila[i] = 0;
        }
    }
    
    // Impresión de resultados por fila
    for (i = 0; i < N; i++) {
        printf("FILA %d EVENTOS %d IMPACTO %lld RACHA %d INICIO %d\n", 
               i + 1, eventos_fila[i], impacto_fila[i], racha_fila[i], inicio_racha_fila[i]);
    }
    
    // Impresión de eventos por columna
    printf("COLUMNAS");
    for (j = 0; j < M; j++) {
        printf(" %d", eventos_columna[j]);
    }
    printf("\n");    
    // Selección de la fila prioritaria con desempates manuales
    int fila_prioritaria = 0;
    int max_racha_g = -1;
    long long max_impacto_g = -1;
    int max_eventos_g = -1;
    
    for (i = 0; i < N; i++) {
        // Si no hay eventos ni racha en esta fila, se evalúa con los criterios normales
        int actualizar = 0;
        if (fila_prioritaria == 0) {
            actualizar = 1;
        } else {
            if (racha_fila[i] > max_racha_g) {
                actualizar = 1;
            } else if (racha_fila[i] == max_racha_g) {
                if (impacto_fila[i] > max_impacto_g) {
                    actualizar = 1;
                } else if (impacto_fila[i] == max_impacto_g) {
                    if (eventos_fila[i] > max_eventos_g) {
                        actualizar = 1;
                    }
                }
            }
        }
        
        if (actualizar == 1) {
            fila_prioritaria = i + 1;
            max_racha_g = racha_fila[i];
            max_impacto_g = impacto_fila[i];
            max_eventos_g = eventos_fila[i];
        }
    }
    
    // Validar si toda la matriz estuvo completamente sin eventos
    int total_eventos_matriz = 0;
    for (i = 0; i < N; i++) {
        total_eventos_matriz += eventos_fila[i];
    }
    
    if (total_eventos_matriz == 0) {
        fila_prioritaria = 0;
    }
    
    printf("PRIORIDAD %d\n", fila_prioritaria);
    
    // Selección de la columna destacada
    int columna_destacada = 0;
    int max_ev_col = -1;
    
    for (j = 0; j < M; j++) {
        if (eventos_columna[j] > max_ev_col) {
            max_ev_col = eventos_columna[j];
            columna_destacada = j + 1;
        }
    }
    
    if (max_ev_col <= 0 || total_eventos_matriz == 0) {
        columna_destacada = 0;
    }
    
    printf("COLUMNA %d\n", columna_destacada);
    
    return 0;
}
 