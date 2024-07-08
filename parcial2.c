#include <stdio.h>

#define FI 1000
#define CO 10
#define MAX_PEDIDOS 200

// Estructura para las autopartes
struct {
    int numero_autoparte;
    float precio;
    int stock;
} 

// Estructura para los empleados
struct {
    int numero_empleado;
    float comision_venta; // En porcentaje
    float monto_total_comision;
    int cantidad_pedidos; // Número de pedidos atendidos
} 

// Estructura para los pedidos
struct {
    int numero_pedido;
    int numero_autoparte;
    int cantidad_pedida;
    int numero_empleado;
    int cumplePedido; // 1 si se puede cumplir el pedido, -1 si no
} 

// Declaración de funciones
void IngresoPedidos(Pedido pedidos[], int num_pedidos, Autoparte autopartes[], Empleado empleados[]);
int hayStock(Autoparte autopartes[], int numero_autoparte, int cantidad_pedida);
void pedidosEmpleados(Empleado empleados[], int num_empleados);
void listadoPrecioAutoparte(Autoparte autopartes[], int num_autopartes);

void main() {
    // Inicializar los lotes de datos
    Autoparte autopartes[FI];
    Empleado empleados[CO];
    Pedido pedidos[MAX_PEDIDOS];

    // Inicializar los datos de autopartes
    for (int i = 0; i < FI; i++) {
        autopartes[i].numero_autoparte = i + 1;
        autopartes[i].precio = (i + 1) * 10.0; // Ejemplo de precio
        autopartes[i].stock = 100;
    }

    // Inicializar los datos de empleados
    for (int i = 0; i < CO; i++) {
        empleados[i].numero_empleado = i + 1;
        empleados[i].comision_venta = 0.01 * (1 + (i % 5)); // Comisión entre 1% y 5%
        empleados[i].monto_total_comision = 0.0;
        empleados[i].cantidad_pedidos = 0;
    }

    // Simulación de pedidos (ejemplo)
    int numero_pedidos = 5; // Supongamos que hay 5 pedidos

    // Invocar funciones
    IngresoPedidos(pedidos, numero_pedidos, autopartes, empleados); // Invocar IngresoPedidos
    pedidosEmpleados(empleados, CO); // Invocar pedidosEmpleados
    listadoPrecioAutoparte(autopartes, FI); // Invocar listadoPrecioAutoparte

    // Imprimir los datos inicializados
    printf("Autopartes:\n");
    for (int i = 0; i < 5; i++) { // Solo imprimir los primeros 5 para no saturar la salida
        printf("Numero de Autoparte: %d, Precio: %.2f, Stock: %d\n", autopartes[i].numero_autoparte, autopartes[i].precio, autopartes[i].stock);
    }

    printf("\nEmpleados:\n");
    for (int i = 0; i < CO; i++) {
        printf("Numero de Empleado: %d, Comision sobre Ventas: %.2f%%, Monto Total de Comision: %.2f, Cantidad de Pedidos Atendidos: %d\n",
               empleados[i].numero_empleado, empleados[i].comision_venta * 100, empleados[i].monto_total_comision, empleados[i].cantidad_pedidos);
    }

    printf("\nPedidos:\n");
    for (int i = 0; i < numero_pedidos; i++) {
        printf("Numero de Pedido: %d, Numero de Autoparte: %d, Cantidad Pedida: %d, Numero de Empleado: %d, Cumple Pedido: %d\n",
               pedidos[i].numero_pedido, pedidos[i].numero_autoparte, pedidos[i].cantidad_pedida, pedidos[i].numero_empleado, pedidos[i].cumplePedido);
    }

    return;
}

// Definición de la función IngresoPedidos
void IngresoPedidos(Pedido pedidos[], int num_pedidos, Autoparte autopartes[], Empleado empleados[]) {
    for (int i = 0; i < num_pedidos; i++) {
        pedidos[i].numero_pedido = i + 1;
        pedidos[i].numero_autoparte = (i % FI) + 1;
        pedidos[i].cantidad_pedida = 10 * (i + 1);
        pedidos[i].numero_empleado = (i % CO) + 1;

        // Verificar si el pedido se puede cumplir
        if (hayStock(autopartes, pedidos[i].numero_autoparte, pedidos[i].cantidad_pedida)) {
            pedidos[i].cumplePedido = 1;

            // Actualizar stock de autopartes
            autopartes[pedidos[i].numero_autoparte - 1].stock -= pedidos[i].cantidad_pedida;

            // Calcular y actualizar la comisión del empleado
            float venta_total = pedidos[i].cantidad_pedida * autopartes[pedidos[i].numero_autoparte - 1].precio;
            float comision = venta_total * empleados[pedidos[i].numero_empleado - 1].comision_venta;
            empleados[pedidos[i].numero_empleado - 1].monto_total_comision += comision;

            // Incrementar el contador de pedidos del empleado
            empleados[pedidos[i].numero_empleado - 1].cantidad_pedidos++;
        } else {
            pedidos[i].cumplePedido = -1;
        }
    }
}

// Definición de la función hayStock
int hayStock(Autoparte autopartes[], int numero_autoparte, int cantidad_pedida) {
    if (autopartes[numero_autoparte - 1].stock >= cantidad_pedida) {
        return 1;
    } else {
        return;
    }
}

// Definición de la función pedidosEmpleados
void pedidosEmpleados(Empleado empleados[], int num_empleados) {
    printf("\nCantidad de pedidos atendidos por cada empleado:\n");
    for (int i = 0; i < num_empleados; i++) {
        printf("Numero de Empleado: %d, Cantidad de Pedidos Atendidos: %d\n",
               empleados[i].numero_empleado, empleados[i].cantidad_pedidos);
    }
}

// Definición de la función listadoPrecioAutoparte
void listadoPrecioAutoparte(Autoparte autopartes[], int num_autopartes) {
    // Algoritmo de ordenación (Bubble Sort)
    for (int i = 0; i < num_autopartes - 1; i++) {
        for (int j = 0; j < num_autopartes - 1 - i; j++) {
            if (autopartes[j].precio < autopartes[j + 1].precio) {
                // Intercambiar autopartes[j] y autopartes[j + 1]
                Autoparte temp = autopartes[j];
                autopartes[j] = autopartes[j + 1];
                autopartes[j + 1] = temp;
            }
        }
    }

    // Imprimir el listado ordenado
    printf("\nListado de Autopartes ordenado por Precio (descendente):\n");
    for (int i = 0; i < num_autopartes; i++) {
        printf("Numero de Autoparte: %d, Precio: %.2f, Stock: %d\n",
               autopartes[i].numero_autoparte, autopartes[i].precio, autopartes[i].stock);
    }
}
