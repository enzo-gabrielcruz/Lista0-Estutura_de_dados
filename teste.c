int main() {
    FILE *file_in = fopen("L0Q1.in", "r");
    FILE *file_out = fopen("L0Q1.out", "w");

    if (!file_in || !file_out) {
        perror("Erro ao abrir arquivos");
        return 1;
    }

    while (fgets(line, MAX_LINE , file_in))  {
        char *line = lines[l];
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

        double shortcut = euclidean_distance(original_points[0], original_points[count - 1]);

        fprintf(file_out, " distance %.2f shortcut %.2f", distance, shortcut);

        fprintf(file_out, "\n");
        
    }

    fclose(file_in);
    fclose(file_out);
    remover_ultima_linha_em_branco("L0Q1.out");
} 