

---

# Permutaciones Gráciles

Este programa genera todas las permutaciones **gráciles** de los números del 1 al `n`, donde se define una permutación grácil como aquella en la que las diferencias absolutas entre números consecutivos son todas **únicas**.

---

## Descripción

El algoritmo utiliza una función recursiva optimizada mediante **máscaras de bits** para:

- **Evitar repetir elementos** en una permutación (`usedMask`).
- **Evitar repetir diferencias** entre números consecutivos (`diffMask`).
- **Realizar podas tempranas** cuando una diferencia ya ha sido utilizada, lo cual reduce drásticamente el espacio de búsqueda.

Este enfoque mejora el rendimiento del algoritmo, pero **puede generar desbordamiento de pila** cuando `n` es muy grande debido a la profundidad de la recursión.

---

## Alternativa sin recursión

El mismo algoritmo puede ser implementado utilizando una estructura iterativa (por ejemplo, una **pila simulada** con estructuras `struct` o arrays) para evitar el uso de la pila del sistema.

Esto es especialmente útil en entornos con recursos limitados o cuando `n` se acerca al máximo (`MAX_N = 20`), ya que la versión recursiva puede agotar la pila del programa dependiendo del sistema operativo y configuración del compilador.

---

## ¿Cómo funcionan las máscaras?

### `usedMask`

Variable de tipo `int` que representa, con bits, qué números ya se usaron en la permutación actual.

Ejemplo: si `n = 5` y `usedMask = 0b10110`, quiere decir que los números 2, 3 y 5 ya fueron utilizados.

Se calcula qué números están disponibles así:

```c
int available = (~usedMask) & ((1 << (n + 1)) - 2);
```

Esto obtiene una máscara con bits en 1 para los números aún no utilizados entre 1 y `n`.

---

### `diffMask`

Similar a `usedMask`, pero cada bit representa si una diferencia ya ha sido usada.  
Por ejemplo, si ya se usó la diferencia de 3, se activa el bit 3:

```c
diffMask |= (1 << diff);
```

Esto permite verificar rápidamente si una nueva diferencia ya está repetida, lo que invalida la permutación.

---

## Ventajas del uso de máscaras

- **Velocidad**: Las operaciones con bits (`&`, `|`, `~`, `^`, `<<`, `>>`) son de muy bajo costo computacional.
- **Eficiencia de memoria**: Se reduce el uso de arrays y estructuras más grandes.
- **Podas tempranas**: Permite descartar caminos inválidos en la recursión rápidamente.
- **Escalabilidad**: Permite calcular resultados hasta `n = 20` de forma eficiente.

---

## Ejemplo de ejecución

```bash
Introduce el valor de N (máx. 20): 5
Total de permutaciones graciles generadas: 10
Tiempo de ejecución: 0.000038 segundos
```

---

