// EQUIPE: ENZO GABRIEL CALADO DA CRUZ E JOÃO NETO
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LINE 501
#define MAX_POINTS 100
#define MAX_LINES 1000  // Para armazenar até 1000 linhas de entrada

typedef struct {
    double x, y;
} Point;

double euclidean_distance(Point a, Point b) {
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

double distance_to_origin(Point p) {
    return sqrt(p.x * p.x + p.y * p.y);
}

int compare_points(const void *a, const void *b) {
    Point *pa = (Point *)a;
    Point *pb = (Point *)b;
    double da = distance_to_origin(*pa);
    double db = distance_to_origin(*pb);
    if (da < db) return -1;
    else if (da > db) return 1;
    return 0;
}

void remover_ultima_linha_em_branco(const char *file_out) {
    FILE *arquivo = fopen(file_out, "rb");
    if (!arquivo) {
        perror("Erro ao abrir arquivo para leitura");
        return;
    }

    // Descobre tamanho do arquivo
    fseek(arquivo, 0, SEEK_END);
    long tamanho = ftell(arquivo);
    rewind(arquivo);

    // Lê todo o conteúdo
    char *conteudo = malloc(tamanho + 1);
    if (!conteudo) {
        fclose(arquivo);
        fprintf(stderr, "Erro de alocação\n");
        return;
    }

    fread(conteudo, 1, tamanho, arquivo);
    conteudo[tamanho] = '\0';
    fclose(arquivo);

    // Remove último \n se existir
    if (tamanho > 0 && conteudo[tamanho - 1] == '\n') {
        conteudo[tamanho - 1] = '\0';
        tamanho--;
    }

    // Regrava o arquivo sem a última quebra de linha
    arquivo = fopen(file_out, "wb");
    if (!arquivo) {
        perror("Erro ao abrir arquivo para escrita");
        free(conteudo);
        return;
    }

    fwrite(conteudo, 1, tamanho, arquivo);
    fclose(arquivo);
    free(conteudo);
}
int main() {
    FILE *file_in = fopen("L0Q1.in", "r");
    FILE *file_out = fopen("L0Q1.out", "w");

    if (!file_in || !file_out) {
        perror("Erro ao abrir arquivos");
        return 1;
    }

    char line[MAX_LINE];

    while (fgets(line, MAX_LINE, file_in)) {
        Point original_points[MAX_POINTS];
        Point sorted_points[MAX_POINTS];
        int count = 0;

        char *token = strtok(line, "()");
        while (token != NULL) {
            double x, y;
            if (sscanf(token, "%lf,%lf", &x, &y) == 2) {
                original_points[count].x = x;
                original_points[count].y = y;
                sorted_points[count] = original_points[count];
                count++;
            }
            token = strtok(NULL, "()");
        }

        qsort(sorted_points, count, sizeof(Point), compare_points);

        fprintf(file_out, "points");
        for (int i = 0; i < count; i++) {
            fprintf(file_out, " (%.0f,%.0f)", sorted_points[i].x, sorted_points[i].y);
        }

        double distance = 0;
        for (int i = 0; i < count - 1; i++) {
            distance += euclidean_distance(original_points[i], original_points[i+1]);
        }

        double shortcut = 0;
        if (count >= 2) {
            shortcut = euclidean_distance(original_points[0], original_points[count - 1]);
        }

        fprintf(file_out, " distance %.2f shortcut %.2f\n", distance, shortcut);
    }

    fclose(file_in);
    fclose(file_out);
    remover_ultima_linha_em_branco("L0Q1.out");
}






