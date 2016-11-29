
<?php 
// Incluimos el encabezado del documento
include 'includes/header.inc';

// Conectamos a la base de datos
conectar();

if (isset($_POST['usuario'])) { //Comprobamos si existe una variable de usuario a recibir
    $user = $_POST['usuario']; //Volcamos el usuario
    $pass = $_POST['password']; //Volcamos el password

    try { //Lanzamos la consulta para averiguar si existe usuario con dicha pass
        $consulta = "SELECT * FROM usuarios WHERE login = :login AND password = :pass";

        $resultado = $GLOBALS['con']->prepare($consulta);
        $resultado->bindParam(":login", $user);
        $resultado->bindParam(":pass", $pass);

        $resultado->execute();

        $registro = $resultado->fetch(); //Obtenemos el resultado

    } catch (Exception $ex) {
        echo "<div class='errcon'><p>Se ha producido error " . $e->getMessage() . "</p></div>";
    }


    if ($resultado->rowCount() > 0) { //En el caso de existir resultados, continuamos.
        ?>

        <!-- Conformamos el formulario con el que trabajaremos -->
        <form name="form" action="user.php" method="post">

        <h4 class="perfect">Bienvenido <?php echo $registro['nombre'] ?></h4>

        <!-- Conformamos el menu de usuario -->    
        <fieldset class="menu">
            <input type="submit" name="accion" value="Ingreso" />
            <input type="submit" name="accion" value="Pago" />
            <input type="submit" name="accion" value="Devolución" />
            <input type="submit" name="accion" value="Movimientos" />
            <input type="submit" name="accion" value="Salir" />
        </fieldset>        

        <?php

        /*
         * Capturamos las acciones del boton accion del formulario, y lanzamos la funcion necesaria
         * Practicamente es una mejora del ejercicio anterior, sustituyendo lo que seria el array 
         * persistente que usabamos en la unidad anterior por las consultas a BD.
         * 
         * Unicamente se mantiene el hidden a efectos de perpetuar la sesion del usuario activo y asi
         * poder evitar accesos indeseados externamente.
         */
        if (isset($_POST['accion'])) {
            $accion = $_POST['accion'];

            switch ($accion) {
                case 'Ingreso':
                    formulario('Ingreso'); //lanzamos el formulario en modo ingreso
                    break;

                case 'Ingresar':
                    ingreso_pago($user); //En el caso de confirmar el ingreso, se formalizará en la BD
                    break;

                case 'Pago':
                    formulario('Pago'); //Lanzamos el formulario en modo pago
                    break;

                case 'Pagar':
                    ingreso_pago($user); //En el caso de confirmar el pago, se formalizará en la BD
                    break;

                case 'Devolución':
                    recibos($user); //Se muestra el formulario con el listado de recibos y poder devolver estos
                    break;

                case 'Devolver':
                    devolver($user); //En el caso de confirmar la devolucion, se formalizará en la BD
                    break;

                case 'Cancelar': //Acción por defecto, anulará cualquier selección
                    break;

                case 'Movimientos':
                    movimientos($user); //En el caso de solicitar Movimientos, se mostrará el panel de movimientos de la cuenta
                    break;

                case 'Salir':
                    desconectar(); //Se desconecta de la BD
                    header('Location: index.php'); //Redirigimos a la página principal. Se pierde el usuario activo.
                    break;

                default:
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

//Incluimos el pie de página del documento
include 'includes/footer.inc';
?>
