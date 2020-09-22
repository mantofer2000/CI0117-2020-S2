# CI0117 - Laboratorio 4

##### Programación Concurrente

* ##### B82957 - Marco Ferraro
* ##### B86524 - Gabriel Revillat

## Problema: "La barbería (*barbershop*)"

### Descripción

    Una barbería consiste en una sala de espera con n sillas, 
    y la sala del barbero que contiene a la silla del barbero.
    Si no hay clientes por atender, el barbero se va a dormir.
    Si un cliente entra a la barbería y todas las sillas están ocupadas, el cliente abandona la tienda.
    Si el barbero está ocupado pero hay sillas disponibles, el cliente se sienta en una de esas sillas.
    Si el barbero está dormido, el cliente lo despierta.

### ¿Se puede presentar alguna situación de *deadlock* o *starvation*?

Si los hilos del barbero y los clientes no son coordinados correctamente puede haber un caso de *starvation*. Por ejemplo, si ya no queda ningún cliente pero no se le avisa al barbero, el barbero se va a quedar dormido indefinidamente. 

Ademas, debido al uso de semaforos, se puede generar un deadlock debido a las dependencias entre los clientes y el barbero.

### Solución

#### Función del barbero
```c
    void* barber_method(void* args)
    {
        customer_t* private_data = (customer_t*)args;
        barbershop_t* shared_data = (barbershop_t*)private_data->barber_shop;

        printf("Barber has arrived \n");

        while (stop)
        {

            if (customers_remaining == 0)
            {
                barber_leaves();
                return NULL;
            }

            if (customers_sitting != 0)
            {
                cut_hair();
            }
            else
            {
                barber_sleeps();
            }

        }

        return NULL;   
    }
```
#### Función del cliente
```c
    void* customer_method(void* args)
    {
        customer_t* private_data = (customer_t*)args;
        barbershop_t* shared_data = (barbershop_t*)private_data->barber_shop;

        customer_arrives(private_data->customer_id);

        if (customers sitting < limit waiting room)
        {
            customer_sit();
            getHairCut();
        }
        else
        {
            customer_leaves_full();
        }

        num_customers--;

        return NULL;
    }
```