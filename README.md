# proyecto_clan
Proyecto clan de EDD de arboles

Este proyecto digitaliza los registros genealogicos de una familia del oriente, responsable de la proteccion del shogun, a traves de la conversion de datos de archivos CSV y la construccion de un arbol genealogico dinamico. Se implementa de manera manual la gestion de estructuras dinámicas y se utiliza la técnica de hijo izquierdo – hermano derecho para representar arboles generales.

## Metodología

  Se evita el uso de librerías de estructuras dinámicas prefabricadas, implementando manualmente punteros, listas enlazadas y arboles.  
  Se utiliza la técnica hijo izquierdo – hermano derecho para manejar la jerarquía familiar. Lo que hace cada nodo tenga un unico puntero a su primer hijo y a su siguiente hermano, aplicando correctamente los niveles de jerarquía.
  Antes de cada operación (o al iniciar el menu), se verifica que el lider actual cumpla las condiciones para ser lider (por ejemplo, tener una edad menor o igual a 70 años y estar vivo). Si no cumple, se reasigna automáticamente el liderazgo al siguiente candidato disponible en la sucesión.

Basicamente en lineas generales, el proyecto lo hice basando todo mi enfoque en la consideracion del liderazgo, en la reasignacion del lider al morir o dejar de cumplir las condiciones para serlo, y en la logica para validar esto mismo. Hice la construccion del arbol y luego el codigo de como sera la sucesion con los niveles de jerarquia, siguiendo lo antes mencionado (hijo izquierdo- hermano derecho).
