<!DOCTYPE html>
<!-- Desarrollo Web en Entorno Servidor -->
<!-- Tema 3: Trabajar con bases de datos en PHP -->
<!-- Felipe Rodríguez Gutiérrez -->
<!-- Tarea: 03 Banco DWES -->
<html>
    
<head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title>DWES - Tarea 3 - Felipe Rodríguez Gutiérrez</title>
    <link type="text/css" href="estilos.css" rel="stylesheet" />
    <?php include './includes/funciones.inc'; ?>
</head>

<body>
    
<h1 class="centrado">TAREA 3: BANCO DWES</h1>
    <h2 class="centrado">Felipe Rodríguez Gutiérrez</h2>
    <?php 
    /* Conectamos a la base de datos */
        conectar();
        
        if (isset($_POST['usuario'])) { //Si existe una variable usuario ya sea recibida por el login o por el hidden, que persiste el usuario mientras no salgamos...
            $user = $_POST['usuario'];  //Almacena el login de usuario introducido
            $pass = $_POST['password']; //Almacena el password del usuario introducido
            
            if (($user == 'dwes') AND ($pass == 'dwes')) { //Si coincide el nombre y usuario con el preestablecido como admin (dwes)...
                ?>
                <!-- Conformamos el formulario con el que trabajaremos -->
                <form name="form" action="admin.php" method="post">
                    
                <h4 class="perfect">Bienvenido Administrador!</h4>
                <h3 class="centrado">Menu administración de usuarios</h3>

                <!-- Conformamos el menu de usuario -->    
                <fieldset class="menu">
                    <input type="submit" name="accion" value="Nuevo" />
                    <input type="submit" name="accion" value="Borrar" />
                    <input type="submit" name="accion" value="Editar" />
                    <input type="submit" name="accion" value="Salir" />
                </fieldset>        

                <?php
                
                if (isset($_POST['accion'])) { //Capturamos los valores del boton accion, y lo relacionamos con acciones
                    $accion = $_POST['accion'];
                    
                    switch ($accion) {
                        case 'Nuevo':
                            form_usuario(); //Si pulsamos en Nuevo, mostraremos un formulario de nuevo usuario.
                            break;
                        
                        case 'Agregar':
                            agrega_usuario(); //Si pulsamos en Agregar, agregaremos el usuario a la BD.
                            break;
                        
                        case 'Borrar':
                            usuarios('eliminar'); //Si pulsamos en Borrar, invocamos el listado de usuarios en modo de eliminación
                            break;
                        
                        case 'Eliminar':
                            elimina_usuario(); //Si confirmamos la eliminacion, se procede a la eliminacion de la BD.
                            usuarios('eliminar'); //Volvemos a mostrar el menu de usuarios.
                            break;
                        
                        case 'Editar':
                            usuarios('modificar'); //Si pulsamos en Modificar, invocamos el listado de usuarios en modo edicion
                            break;
                        
                        case 'Modificar':
                            modifica_usuario(); //Si confirmamos, invocamos el formulario con los datos del usuario a modificar
                            break;
                        
                        case 'Actualizar':
                            actualiza_usuario(); //Si confirmamos, se procede a actualizar los datos en la BD.
                            usuarios('modificar'); //Mostramos nuevamente el listado de usuarios actualizado en modo edición
                            break;
                        
                        case 'Salir':
                            desconectar(); //Desconectamos de la BD
                            header('Location: index.php'); //Regresamos a la página principal
                            break;

                        default: //En cualquier otro caso, que no haga nada
                            break;
                    }
                    
                }
                    /*
                     * Campos hidden que perpetuarán el usuario y password introducidas durante la permanencia en el formulario
                     * de esta forma simularemos la sesión abierta por el usuario y evitaremos que puedan acceder a la página desde
                     * el exterior sin haber pasado por el login de usuario.
                     */
                    echo '<input type="hidden" name="usuario" value="'. $user .'">';
                    echo '<input type="hidden" name="password" value="'. $pass . '">';
                ?>
                
                </form> 
                <?php
            } else { //En el caso de haber introducido incorrectamente la clave o el password.
                echo "<div class='errcon'><p>ERROR: USUARIO/CLAVE INCORRECTA</p></div>";
            }

        } else { //En el caso de haber accedido a la web externamente sin haber pasado por la página de login.
            echo "<div class='errcon'><p>ERROR: NO TIENE PERMISOS PARA ACCEDER A ESTA PÁGINA</p></div>";
        }
    ?>
    
</body>
    
</html>