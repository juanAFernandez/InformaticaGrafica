#Generacion coordenadas de textura

Proceso de refinamiento del algoritmo de generación de coordenadas de textura.

##Primera aproximación

La primera versión sería cuando nuestro objetivo es generarlas para un cubo del número de caras que sea pero siempre con una sola cara por revolución y sin tapas, por lo que estaríamos trabajando sólo con la sección central. En esta primera versión sólo se hacen divisiones en la horizontal (eje X) e la imagen.


##Segunda aproximación

En este caso ya debemos generar también coordenadas para las tapas superiores e inferiores, por lo que tendremos que empezar a realizar divisiones en el eje Y de la imagen.