#DWES - Tarea 2

## Enunciado:

Debes crear una aplicación en PHP que gestione la banca electrónica del banco Diodos que vimos en la tarea anterior, añadiéndole otras funcionalidades. En esta ocasión  **TODOS**  los datos serán almacenados en una base de datos en MySQL llamada banca\_electronica (se adjunta el script para la creación de la base de datos:  [banca\_electronica.sql](http://www.juntadeandalucia.es/educacion/gestionafp/datos/tareas/DAW/DWES_14076/2016-17/DAW_DWES_2_2016-17_Individual__842905/banca_electronica.zip)).

El acceso a la base de datos debe hacerse a través del usuario  **dwes**  con contraseña  **dwes**. La conexión debe hacerse mediante  **PDO**.

En la página principal (index.php)  se debe mostrar el menú que de acceso a:

- **Administrar usuarios** : gestión de altas, bajas y modificaciones de los usuarios que pueden acceder a la banca electrónica. Para acceder mostramos un formulario en el que solicitamos el login de administrador y la contraseña (ocultando los caracteres de la contraseña). El login y contraseña de administrador siempre serán los mismos que para acceder a la base de datos (usuario  **dwes**  con contraseña  **dwes** ). Si lo introduce bien se mostrará un nuevo menú:
  - **Nuevo usuario:** Introducimos un nuevo usuario, comprobando que su login no existe en el sistema, que sus datos personales no están vacíos y que la contraseña se introduce 2 veces y es coincidente.
  - **Modificar usuario:**  A partir de un login de usuario, mostraremos sus datos y solicitaremos la modificación de los mismos, excepto el login de usuario.
  - **Borrar usuario:**  A partir de un login, eliminaremos un usuario. Todos sus movimientos de banca electrónica quedarán registrados (no se borran).
  - **Salir:**  Volvemos al menú principal.

- **Iniciar sesión** : Mostramos un formulario en el que solicitamos el login de usuario y su contraseña (ocultando los caracteres de la contraseña). Comprobamos si está registrado en el sistema y en caso afirmativo le permitimos el acceso a la banca electrónica.
Mostramos en el margen superior el nombre y apellidos del usuario y a continuación el menú de la banca electrónica, que no es otro que el desarrollado en la tarea anterior, añadiéndoles una nueva opción:
  - **Últimos movimientos:**  Muestra los últimos 5 movimientos.
  - **Ingresar dinero:**  Formulario de ingreso de dinero.
  - **Pagar recibo:**  Formulario de pago de recibos.
  - **Devolver recibo:**  Formulario de devolución de recibos.
  - **Salir:**  Volvemos al menú principal.

El menú con el que estemos navegando en ese momento, debe aparecer en todas las páginas para permitir la navegación (menú en la parte superior). Por ejemplo, si estamos ingresando dinero, en la parte superior debe aparecer el menú de banca electrónica completo.

Todas las operaciones de inserción/almacenamiento, modificación, eliminación y consulta, deberán realizarse mediante el uso de la base de datos.

Deben usarse funciones al menos para el acceso a la base datos: conexión, acceso y manipulación de datos, etc. Todas estas funciones deben estar definidas en un fichero llamado  **funciones.inc**  que debe ser incluido en todas las páginas de la aplicación.

Debe gestionarse el  **manejo de errores**  al menos siempre que se trabaja con la base de datos. Además deberás avisar cuándo las tablas están vacías, si no existe tal registro, etc.

  **RECOMENDACIONES** :

- Para el campo de fecha usar el nuevo type que incorpora HTML5: `<input type="date" ...>`, pero en algunos navegadores como firefox no funciona (podéis ver su comportamiento en el navegador Chrome por ej.), por lo tanto es imprescindible que aunque lo uséis controleis la entrada del texto introducido con el atributo pattern. (Aquí tenéis ejemplos de su uso:  [http://html5pattern.com/Dates](http://html5pattern.com/Dates)
- Para ocultar los caracteres del campo de contraseña puedes utilizar el `<input type="password"…>`.
- Las opciones del menú pueden ser botones, `<a href..>`, ... pero han de estar siempre visibles.
- Ten en cuenta la longitud máxima de cada uno de los campos de las tablas de la base de datos.

**PARTE II:** **Auto-evaluación**

Por último, tienes que  **AUTO-EVALUARTE** , justificando si fuese necesario las notas de cada apartado. Para ello usarás la plantilla que se encuentra en el apartado de &quot;Recursos Necesarios&quot;.



**NOTAS IMPORTANTES:**

- No se puede hacer ninguna modificación sobre la estructura de la base de datos ni el usuario de acceso a ésta
- La entrega de la tarea consiste en:
  - A la vez que realizas la tarea, elaborar un documento de texto en formato  **.** ODT con una guía (muy resumida, no pierdas demasiado tiempo en esto) y capturas si son necesarias de cada menú de la aplicación, sobre todo para mostrar que funciona, usando títulos, un sumario con índices navegables ([**pincha aquí**](http://aplicacionesysistemas.com/indice-con-libreoffice-writer-video-tutorial/#more-198) para ver una guía de cómo hacerlos o [**aquí**](https://help.libreoffice.org/Writer/Creating_a_Table_of_Contents/es) para la última documentación oficial).
    - El archivo .ODT debe ser editado desde LibreOffice u OpenOffice. En &quot;Archivo -&gt; Propiedades&quot; me debe dar una idea del tiempo que se ha tardado en su edición. Si falta el .ODT restará 1 punto.  **Desde el propio LibreOffice se debe exportar a PDF, lo que generará un PDF con índices navegables a la izquierda**.
  - **En cada apartado hay que apoyar la documentación y comprobar que funciona ** con alguna/s capturas de pantalla. Se recomienda alguna herramienta que agilice el proceso como [**Shutter**](http://shutter-project.org/) (Linux) o [**GreenShot**](http://alternativeto.net/software/greenshot/) (Windows). En alguna de ellas (todas las que se pueda), se debe ver la plataforma con vuestra foto del perfil (la foto que os aparece arriba a la derecha).
  - El fichero . **ZIP**  a subir en la tarea debe contener una carpeta llamada  **Apellido1\_Apellido2\_Nombre\_DWES02\_Tarea**  que contenga:
    - El documento de texto . **ODT**  explicativo y el mismo documento exportado a . PDF. **Si falta el** [**índice**](http://aplicacionesysistemas.com/indice-con-libreoffice-writer-video-tutorial/#more-198) de **contenidos &quot;navegable&quot; en el pdf restará 1 punto.**
    - La hoja de cálculo de auto-evaluación .ODS
    - Una carpeta con todos  **los ficheros necesarios y el proyecto de Netbeans completo. ** Si el programa no es fácilmente distribuible (con librerías incluidas en la carpeta dist y con rutas relativas) y multiplataforma (carpetas con &quot;/&quot;) restará 1 punto.
      - En las propiedades del proyecto PHP de Netbeans, en &quot;Run Configuration&quot; debes seleccionar Run As: PHP Built-in Web Server tal y como se ve en esta imagen:  [http://i.imgur.com/y6K0UwS.png](http://i.imgur.com/y6K0UwS.png)

## Criterios de corrección

| La obtención de la nota de la tarea se hará según los siguientes criterios mostrados en la siguiente tabla:|   |
|---|
|  **Puntuación Máxima**  |**Criterio**    |
|---|---| 
|  Sin calificación | Tarea no entregada o en borrador. |
| 0  |La tarea entregada no se corresponde con lo que se  pide.El fichero está corrupto o no se puede abrir.La tarea se ha entregado fuera de plazo.La tarea ha sido copiada.La estructura de la base de datos ha sido modificada.La aplicación no se puede ejecutar debido a errores.|
| 4  |Parte de la aplicación no se puede ejecutar.La tarea se realiza usando Sesiones, Cookies, AJAX, javascript, etc que se trabajarán en unidades posteriores.|
| 10 |La tarea entregada y que funcione correctamente (que no corresponda a ninguno de los apartados mencionados anteriormente) será corregida según la siguiente valoración:|

Se valorará cada uno de los siguientes items (siempre que se haga usando  **PDO** ):

|   |   | Valor |
| --- | --- | --- |
| **1)Menú inicio.** | Menú siempre visible. | 0,2 |
| **Inicio sesión:** |   |
|  - Ocultación de contraseña en inicio sesión. | 0,1 |
|  - Comprobación de campos en inicio sesión. | 0,1 |
|  - Comprobación de usuario (consulta a la base de datos). | 0,4 |
| **Acceso administrador:** |   |
|  - Ocultación de contraseña en acceso administrador. | 0,1 |
|  - Comprobación acceso administrador (sin acceso a base de datos). | 0,1 |
| **2) Administrar usuarios.  ** | Menú siempre visible. | 0,2 |
| **Nuevo usuario:** |   |
|  - Validación de campos. | 0,2 |
|  - Inserción en la BD. | 0,2 |
| **Modificar usuario:** |   |
|  - Selección de usuario. | 0,2 |
|  - Mostrar datos de usuario (editables). | 0,2 |
|  - Validación de campos. | 0,2 |
|  - Guardar cambios en los datos del usuario. | 0,2 |
| **Borrar usuario:** |   |
|  - Selección de usuario. | 0,2 |
|  - Mostrar datos de usuario (no editables). | 0,2 |
|  - Eliminar usuario de la base de datos. | 0,2 |
| **Salir** | 0,1 |
| **3) Banca electrónica.** | Nombre completo del usuario. | 0,2 |
| Menú siempre visible. | 0,2 |
| **Últimos movimientos:** |   |
|  - Últimos 5 movimientos. | 0,2 |
|  - Formato dinero. | 0,2 |
|  - Tabla completa. | 0,3 |
| **Ingresar dinero:** |   |
|  - Validación de campos. | 0,2 |
|  - Inserción en la BD. | 0,2 |
|  - Mensaje de ingreso correcto y visualización de los últimos 10 movimientos. | 0,1 |
| **Pagar recibos:** |   |
|  - Validación de campos. | 0,2 |
|  - Inserción en la BD. | 0,2 |
|  - Mensaje de pago correcto y visualización de los últimos 10 movimientos. | 0,1 |
| **Devolver recibos:** |   |
|  - Listar sólo recibos del usuario. | 0,4 |
|  - Eliminar recibos individualmente de la BD. | 0,2 |
|  - Mensaje de devolución correcta y visualización de los recibos del usuario. | 0,2 |
| **Salir** | 0,1 |
| **General** | Conexión/desconexión y acceso a la base de datos. | 0,5 |
| Correcta navegación entre páginas. | 0,2 |
| Control de errores mediante excepciones. | 1 |
| Estética y organización de la aplicación. | 1 |
| Estructuración del código (uso de funciones, uso de páginas, inclusión de ficheros externos, documentación del código, variables intuitivas, optimización,…). | 0,2 |
| Impresión general de la aplicación. | 1 |
|   | **10** |



## Recursos necesarios:

**Al menos será necesario tener instalado y configurado XAMPP con Apache y MySQL arrancados, y un editor para php, por ejemplo NetBeans o Notepad++**

-   [Script para la creación de la BD banca\_electronica ](http://www.juntadeandalucia.es/educacion/gestionafp/datos/tareas/DAW/DWES_14076/2016-17/DAW_DWES_2_2016-17_Individual__842905/banca_electronica.zip)(.zip tamaño 2Kb)
- [Plantilla para realizar la tarea](http://www.juntadeandalucia.es/educacion/gestionafp/datos/tareas/DAW/DWES_14076/2016-17/DAW_DWES_2_2016-17_Individual__842905/Apellido1_Apellido2_Nombre_DWES02_Tarea_E2.odt)
- [Plantilla para auto-evaluar la tarea](http://www.juntadeandalucia.es/educacion/gestionafp/datos/tareas/DAW/DWES_14076/2016-17/DAW_DWES_2_2016-17_Individual__842905/Apellido1_Apellido2_Nombre_DWES02_Auto-evaluacion_Tarea02.ods)
- [Manual de php.](http://es1.php.net/manual/es/index.php)

## Páginas de ayuda y consulta de ejemplos:

- [http://html5pattern.com/Dates](http://html5pattern.com/Dates)
- [http://www.w3schools.com/tags/tag\_input.asp](http://www.w3schools.com/tags/tag_input.asp)
- [http://www.w3.org/community/webed/wiki/Es/Elementos\_de\_formulario\_adicionales\_del\_HTML5](http://www.w3.org/community/webed/wiki/Es/Elementos_de_formulario_adicionales_del_HTML5)
- [http://mytutorials85.blogspot.com.es/2012/04/formularios-en-html5.html](http://mytutorials85.blogspot.com.es/2012/04/formularios-en-html5.html)
