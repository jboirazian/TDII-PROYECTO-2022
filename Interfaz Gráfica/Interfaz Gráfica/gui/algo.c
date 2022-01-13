    char array[] = "YOUR TEXT HERE";
    FILE *temp_file=fopen("C:\\Users\\Administrator\\Desktop\\TD2\\Interfaz Gráfica\\gui\\temp.txt","w");
    fputs(array, temp_file);
    fclose(temp_file);
