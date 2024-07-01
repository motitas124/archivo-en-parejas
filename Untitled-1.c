#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    int id;
    char nombre[50];
    int cantidad;
    float precio;
} Producto;

void agregarProducto();
void mostrarInventario();
void buscarProducto();

int main() {
    int opcion;

    do {
        printf("\n--- Menú de Inventario ---\n");
        printf("1. Agregar Producto\n");
        printf("2. Mostrar Inventario\n");
        printf("3. Buscar Producto\n");
        printf("4. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                agregarProducto();
                break;
            case 2:
                mostrarInventario();
                break;
            case 3:
                buscarProducto();
                break;
            case 4:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opción no válida\n");
        }
    } while(opcion != 4);

    return 0;
}

void agregarProducto() {
    FILE *archivo = fopen("inventario.txt", "a");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    Producto producto;
    printf("Ingrese ID del producto: ");
    scanf("%d", &producto.id);
    printf("Ingrese nombre del producto: ");
    scanf("%s", producto.nombre);
    printf("Ingrese cantidad del producto: ");
    scanf("%d", &producto.cantidad);
    printf("Ingrese precio del producto: ");
    scanf("%f", &producto.precio);

    fprintf(archivo, "%d %s %d %f\n", producto.id, producto.nombre, producto.cantidad, producto.precio);
    fclose(archivo);
    printf("Producto agregado exitosamente.\n");
}

void mostrarInventario() {
    FILE *archivo = fopen("inventario.txt", "r");
    if (archivo == NULL) {
        printf("No hay productos en el inventario.\n");
        return;
    }

    Producto producto;
    printf("\n--- Inventario ---\n");
    while (fscanf(archivo, "%d %s %d %f", &producto.id, producto.nombre, &producto.cantidad, &producto.precio) != EOF) {
        printf("ID: %d, Nombre: %s, Cantidad: %d, Precio: %.2f\n", producto.id, producto.nombre, producto.cantidad, producto.precio);
    }
    fclose(archivo);
}

void buscarProducto() {
    FILE *archivo = fopen("inventario.txt", "r");
    if (archivo == NULL) {
        printf("No hay productos en el inventario.\n");
        return;
    }

    int idBuscado;
    printf("Ingrese ID del producto a buscar: ");
    scanf("%d", &idBuscado);

    Producto producto;
    int encontrado = 0;
    while (fscanf(archivo, "%d %s %d %f", &producto.id, producto.nombre, &producto.cantidad, &producto.precio) != EOF) {
        if (producto.id == idBuscado) {
            printf("Producto encontrado: ID: %d, Nombre: %s, Cantidad: %d, Precio: %.2f\n", producto.id, producto.nombre, producto.cantidad, producto.precio);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Producto con ID %d no encontrado.\n", idBuscado);
    }
    fclose(archivo);
}
