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

### Solución

#### Función del barbero
```c
    void* barber_method(void* args)
    {
        customer_t* private_data = (customer_t*)args;
        barbershop_t* shared_data = (barbershop_t*)private_data->barber_shop;

        printf("Barber has arrived \n");

        int stop = 1;
        size_t customers_remaining = shared_data->num_customers;
        size_t customers_sitting = 0;

        while (stop)
        {
            random_sleep(1500, 3000);

            pthread_mutex_lock(&shared_data->mutex);
                customers_remaining = shared_data->num_customers;
                customers_sitting = shared_data->customers_sitting;
            pthread_mutex_unlock(&shared_data->mutex);

            if (customers_remaining == 0)
            {
                barber_leaves();
                return NULL;
            }

            if (customers_sitting != 0)
            {
                sem_post(&shared_data->customer_semaphore);
                random_sleep(1500, 3000);
                cut_hair();
                random_sleep(1500, 3000);
                sem_post(&shared_data->barber_chair);
            }
            else
            {
                barber_sleeps();
                sem_wait(&shared_data->barber_semaphore);
                barber_wakes();
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

        if (shared_data->customers_sitting < shared_data->num_waiting_room)
        {
            sem_post(&shared_data->barber_semaphore);

            pthread_mutex_lock(&shared_data->mutex);
                shared_data->customers_sitting++;    
                customer_sits(private_data->customer_id);
            pthread_mutex_unlock(&shared_data->mutex);

            sem_wait(&shared_data->customer_semaphore);

            pthread_mutex_lock(&shared_data->mutex);
                shared_data->customers_sitting--;   
            pthread_mutex_unlock(&shared_data->mutex);        

            get_haircut(private_data->customer_id); 
            sem_wait(&shared_data->barber_chair);
            customer_leaves(private_data->customer_id);
        }
        else
        {
            customer_leaves_full(private_data->customer_id);
        }

        pthread_mutex_lock(&shared_data->mutex);
            shared_data->num_customers--;
        pthread_mutex_unlock(&shared_data->mutex);

        if (shared_data->num_customers == 0)
        {
          sem_post(&shared_data->barber_semaphore);  
        }

        return NULL;
    }
```