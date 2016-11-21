<?php
/* 
 * CODIGO CREADO BAJO LICENCIA CREATIVE COMMONS
 * Reconocimiento - NoComercial - CompartirIgual (by-nc-sa): 
 * No se permite un uso comercial de la obra original ni de las posibles obras
 * derivadas, la distribución de las cuales se debe hacer con una licencia igual
 * a la que regula la obra original.
 */

/**
 * Función que conectará con la base de datos. A modificar la IP por localhost 
 * dado que lkas pruebas se han realizado con un servidor remoto.
 * 
 * @global PDO $con conexión a la base de datos.
 */
function conectar(){
    $db_host = 'localhost';  //  hostname Por defecto: localhost
    $db_name = 'banca_electronica';  //  databasename
    $db_user = 'dwes';  //  username
    $user_pw = 'dwes';  //  password

    try {
        global $con; //Se realiza como variable global para tener la misma disponible en cualquier página
        $con = new PDO('mysql:host='.$db_host.'; dbname='.$db_name, $db_user, $user_pw);
        $con->exec("set names utf8");
    } catch (PDOException $e) { //Se capturan los mensajes de error
        $err = $e->getCode();
        $msj = $e->getMessage(); 
        echo "<div class='errcon'><p>" . $err . " " . $msj . "</p></div>"; //Se devuelven los mismos si existieran
    }
}

/**
 * Función que desconecta de la sesion activa a la base de datos
 */
function desconectar() {
    try {
        $GLOBALS['dwes'] = null;
    } catch (PDOException $e) {
        $err = $e->getCode(); 
        $msj = $e->getMessage(); 
        echo "<div class='errcon'><p>" . $err . " " . $msj . "</p></div>";
    }
}

/**
 * Función que muestra el login de acceso. Dependiendo del parametro introducido
 * la acción del login será diferente aligiendo si es de tipo admin o user, por
 * lo que el acion post se modificaria (user.php o admin.php)
 * 
 * El resto, es un simple formulario
 * 
 * @param type $tipo (user o admin)
 */
function acceso($tipo) {
    echo "<form id='signup' action='".$tipo.".php' method='post'>";
        ?>
        <div class="header">
            <h3>Acceso</h3>
            <p>Debes rellenar este formulario para acceder</p>
        </div>

        <div class="inputs">
            <label>Usuario</label>
            <input type="text" name="usuario" placeholder="Usuario" autofocus />
            <label>Password</label>
            <input type="password" name="password" placeholder="Password" />
            <input id="submit" type="submit" name="enviar" value="INGRESAR" />
        </div>
    </form>
<?php
}

/**
 * Formulario que muestra los usuarios activos en la página. el parametro modo
 * establecerá si el modo a mostrar es para eliminar o para modificar el usuario
 * 
 * @param type $modo a elegir entre 'eliminar' o 'modificar'
 */
function usuarios($modo){
    
    try { //Realizamos una consulta para comprobar los usuarios existentes y se vuelca en un array
        $consulta = "SELECT * FROM usuarios";

        $resultado = $GLOBALS['con']->prepare($consulta);
        $resultado->execute(array());
    } catch (PDOException $e) {
        echo "<div class='errcon'><p>Se ha producido error " . $e->getMessage() . "</p></div>";
    }
    /* Se prepara el acabado de la tabla a mostrar */
    echo "<h4 class='centrado'>Usuarios activos</h4>";
    
    echo "<table>";
    echo "<tr class='encabezado'><th>#</th><th>Usuario</th><th>Password</th><th>Nombre</th><th>Fecha Nacimiento</th></tr>";
    
    if ($resultado->rowCount() > 0) { //Si el numero de resultados es mayor que cero (existen resultados a mostrar)
       
        foreach ($resultado as $usuarios) { //Ppor cada resultado como un usuario...
            echo "<tr>";
            echo "<td class='centrado'><input type='radio' name='indice' value='" . $usuarios['login'] . "'></td><td>" . $usuarios['login'] . "</td><td>" . $usuarios['password'] . "</td><td>" . $usuarios['nombre'] . "</td><td>" . $usuarios['fNacimiento'] . "</td>";
            echo "</tr>";
        }
        echo "</table>"; 
        
        if ($modo == "eliminar"){ //Si se ha indicado el modo eliminar, se muestra el boton "Eliminar"
            echo "<div class='centrado'><input type='submit' name='accion' value='Eliminar'> <input type='submit' name='accion' value='Cancelar'></div>";
        } else if ($modo == "modificar") { //En caso contrario, mostramos el boton de "Modificar"
            echo "<div class='centrado'><input type='submit' name='accion' value='Modificar'> <input type='submit' name='accion' value='Cancelar'></div>";
        } else { //Cualquier otro error que se escape, lo mostramos de igual manera
            echo "<div class='errcon'><p>ERROR: ESTO ES UN ERROR DESCONOCIDO</p></div>";
        }

    } else { //En el caso de no existir elementos, lo indicamos
        echo "<tr class='centrado'><td colspan='5'>No existen usuarios que visualizar</td></tr></table>";
    }
}

/**
 * Función del formulario de usuario. Con parametros por defecto pero con la posibilidad
 * de modificar los mismos. Para poder recuperar los datos en caso de error.
 * 
 * El parametro acción por defecto será para añadir usuarios, pero podra elegirse entre
 * "Agregar" o "modificar".
 * 
 * @param type $login login del usuario
 * @param type $nombre nombre completo del usuario
 * @param type $fNac fecha de nacimiento del usuario
 * @param type $accion accion que debe tomar el formulario, para agregar o modificar el usuario, definirá posteriomente la posibilidad
 * de edicion del campo login.
 */
function form_usuario($login = "", $nombre = "", $fNac = "", $accion = "Agregar"){
?>
    <fieldset class="menu">
            <legend>Ingreso nuevo usuario</legend>
                <div class="inputs">
                    <?php if ($accion == "Agregar") { //Si es para agregar un usuario, el campo login será normal y corriente
                        ?><label>Login</label> <input type="text" name="login" value="<?php echo $login ?>" /> <br/>
                        <?php
                    } else { //En el caso de modificar un usuario, se mantendra el usuario como solo lectura para evitar modificaciones del usuario
                        ?><label>Login</label> <input type="text" name="login" value="<?php echo $login ?>" readonly /> <br/>
                        <?php //Resto del formulario. El campo fecha posee un patrón para evitar introduccion de fechas incorrectamente. En el caso de ser usuario a modificar, recibiran los valores de fecha y nombre (el password al no verse es tonteria incluirlo).
                    }?> 
                    <label>Password</label> 
                    <input type="password" name="pass" /> <br/>
                    <label>Repitepass</label> 
                    <input type="password" name="pass2" /> <br/>
                    <label>Nombre</label> 
                    <input type="text" name="nombre" value="<?php echo $nombre ?>" /> <br/>
                    <label>Fecha Nacimiento</label> 
                    <input class="calendario" type="date" pattern="(?:19|20)[0-9]{2}-(?:(?:0[1-9]|1[0-2])-(?:0[1-9]|1[0-9]|2[0-9])|(?:(?!02)(?:0[1-9]|1[0-2])-(?:30))|(?:(?:0[13578]|1[02])-31))" name="fNac" value="<?php echo $fNac ?>" /> <br/>
                    <input type="submit" name="accion" value="<?php echo $accion ?>">
                </div>

    </fieldset>
<?php
}

/**
 * Función para agregar un usuario, recibe los datos del formulario de usuario y los añade a la base de datos.
 */
function agrega_usuario() {

    if (isset($_POST['accion'])) { //Si ha recibido la acción...
        
        /* Recepciona en variables los datos obtenidos por el formulario */
        $login = $_POST['login'];
        $pass = $_POST['pass'];
        $pass2 = $_POST['pass2'];
        $nombre = $_POST['nombre'];
        $fNac = $_POST['fNac'];
        
        /* Valida los datos recibidos, volcandolos en un flag de control*/
        $flag = validar_usuario($login, $pass, $pass2, $nombre, $fNac);
        
        if ($flag) { //Si el flag de control es negativo...
            echo $flag; //Mostrará los errores obtenidos....
            form_usuario($login, $nombre, $fNac); //Muestra de nuevo el formulario con los datos introducidos para corregir
        } else { //caso de que todo este correcto... insertamos el usuario
            
            try { //Preparamos la consulta
                $consulta = "INSERT INTO USUARIOS (login, password, nombre, fNacimiento) VALUES (:login, :pass, :nombre, :fNac)";

                $resultado = $GLOBALS['con']->prepare($consulta);
                $resultado->bindParam(":login", $login);
                $resultado->bindParam(":pass", $pass);
                $resultado->bindParam(":nombre", $nombre);
                $resultado->bindParam(":fNac", $fNac);
                $resultado->execute();

                echo "<p class='perfect'>Se ha creado el usuario " . $login . " correctamente</p>"; //Mensaje de feedback a mostrar...
                //usuarios();

            } catch (PDOException $e) { //En caso de errores
                echo "<div class='errcon'><p>Se ha producido error " . $e->getMessage() . "</p></div>"; //Se captura el error y se muestra
            }
        }
        
    } else { //En el caso de existir error desconocido no controlado, se muestra mensaje
        echo "<div class='errcon'><p>ERROR: ESTO ES UN ERROR DESCONOCIDO</p></div>";
    }
}

/**
 * Funcion para eliminar un usuario, recibe los datos del usuario elegido y lo elimina de la base de datos
 */
function elimina_usuario() {
    if ((isset($_POST['indice'])) AND ($_POST['indice']) != NULL) { //Si existe usuario elegido o este no es nulo.... (el usuario en sí)

        try { //Preparamos la consulta de eliminacion con los datos
            $consulta = "DELETE FROM usuarios WHERE login = :login";
            
            $resultado = $GLOBALS['con']->prepare($consulta);
            $resultado->bindParam(":login", $_POST['indice']); //Parametrizamos la consulta con el login del usuario a eliminar
            
            $resultado->execute(); //Ejecutamos la consulta
            
        } catch (PDOException $e) { //En caso de errores
            echo "<div class='errcon'><p>Se ha producido error " . $e->getMessage() . "</p></div>"; //Se captura el error y se muestra
        }

        echo "<p class='perfect'><strong>INFO:</strong> Ha eliminado al usuario " . $_POST['indice'] . "</p>"; //Mensaje de feedback a mostrar
    } else {
        echo "<p class='error'><strong>INFO:</strong> No ha seleccionado ningún usuario a eliminar</p>"; //Mensaje en el caso de no haber seleccionado ningun elemento de indice y haber pulsado el boton de Devolver
    }
}

/**
 * Funcion para modificar al usuario. Similar a la anterior, salvo que en este caso obtendremos los valores de dicho usuario
 * para reenviarlos al formulario de usuario y poder modificar posteriormente el mismo en la base de datos
 */
function modifica_usuario() {
    if ((isset($_POST['indice'])) AND ($_POST['indice']) != NULL) { //Si existe usuario elegido o este no es nulo.... (el usuario en sí) 

        try { //Preparamos la consulta para obtener el usuario
            $consulta = "SELECT * FROM usuarios WHERE login = :login";
            
            $resultado = $GLOBALS['con']->prepare($consulta);
            $resultado->bindParam(":login", $_POST['indice']); //Parametrizamos la consulta con el login del usuario a eliminar
            
            $resultado->execute(); //Ejecutamos la consulta
            
            $registro = $resultado->fetch(); //Obtenemos el registro obtenido de la consulta
            
            /* volcamos los datos en las variables a pasar como parametros a la funcion */
            $login = $registro['login'];
            $nombre = $registro['nombre'];
            $fNac = $registro['fNacimiento'];
            
            /* Invocamos la funcion y le pasamos los parametros obtenidos. Se indica la forma de accion del formulario */
            form_usuario($login, $nombre, $fNac, $accion = 'Actualizar');
            
        } catch (PDOException $e) { //En caso de errores
            echo "<div class='errcon'><p>Se ha producido error " . $e->getMessage() . "</p></div>"; //Se captura el error y se muestra
        }
        
    } else {
        echo "<p class='error'><strong>INFO:</strong> No ha seleccionado ningún usuario a eliminar</p>"; //Mensaje en el caso de no haber seleccionado ningun elemento de indice y haber pulsado el boton de Modificar
    }
}

/**
 * Funcion que actualiza los datos del usuario en formulario
 */
function actualiza_usuario() {
    if (isset($_POST['accion'])) { //Si se ha recepcionado una acción...
        
        /* Volcamos los datos obtenidos en variables */
        $login = $_POST['login'];
        $pass = $_POST['pass'];
        $pass2 = $_POST['pass2'];
        $nombre = $_POST['nombre'];
        $fNac = $_POST['fNac'];
        
        /* Validamos dichas variables ...*/
        $flag = validar_datos($pass, $pass2, $nombre, $fNac);
        
        if ($flag) { //Caso de existir errores...
            echo $flag; //Muestra dichos errores
            form_usuario($login, $nombre, $fNac); //Vuelve a presentar el formulario con los datos introducidos para su corrección
        } else { //caso de que todo este correcto... insertamos el usuario
            
            try { //Preparamos la consulta con los valores validados
                $consulta = "UPDATE USUARIOS SET password = :pass, nombre = :nombre, fNacimiento = :fNac WHERE login = :login";

                $resultado = $GLOBALS['con']->prepare($consulta);
                $resultado->bindParam(":login", $login);
                $resultado->bindParam(":pass", $pass);
                $resultado->bindParam(":nombre", $nombre);
                $resultado->bindParam(":fNac", $fNac);
                $resultado->execute();

                echo "<p class='perfect'>Se ha modificado el usuario " . $login . " correctamente</p>"; //Mensaje de Feedback

            } catch (Exception $e) { //Si existen errores
                echo "<div class='errcon'><p>Se ha producido error " . $e->getMessage() . "</p></div>"; //Se captura el error y se muestra por pantalla
            }
        }
        
    } else { //En el caso de existir errores desconocidos
        echo "<div class='errcon'><p>ERROR: ESTO ES UN ERROR DESCONOCIDO</p></div>";
    }
}

/**
 * A partir de este punto la mayoria de las funciones son las usadas en el ejercicio anterior pero mejoradas y cambiado el sistema de recuperacion de
 * los datos introducidos incorrectamente para poder ser corregidos
 */

/**
 * Funcion con el formulario válido para ingresos y pagos. Con parametros por defecto.
 * En el caso de introducir mal alguno de los parametros o no ser validado recuperará dicho valor para ser corregido
 * 
 * @param type $accion accion que se desea que tome el formulario "Ingresar" o "Pagar" para que realice esta acción
 * @param type $fecha parametro fecha
 * @param type $concepto parametro concepto
 * @param type $cantidad parametro cantidad
 */
function formulario ($accion, $fecha="", $concepto="", $cantidad=""){
    if ($accion === 'Ingreso'){ //Si se captura Ingreso...
        $etiqueta = "Formulario de ingreso bancario"; //Nombre de la etiqueta del fieldset
        $boton = "Ingresar"; //Nombre del boton
        echo "<h4 class='centrado'>INFO: Rellene los siguientes campos para realizar un ingreso de efectivo</h4>";
    } else { 
        $etiqueta = "Formulario de pagos bancarios"; //Nombre de la etiqueta del fieldset
        $boton = "Pagar"; //Nombre del boton
        echo "<h4 class='centrado'>INFO: Rellene los siguientes campos para realizar el pago de un recibo</h4>";
    }
?>
    <!-- Formulario a mostrar, reutilizable para pagos e ingresos -->
    <fieldset class="menu"> 
        <?php echo "<legend>" . $etiqueta . "</legend>"; ?>
            Fecha: <input type="date" pattern="(?:19|20)[0-9]{2}-(?:(?:0[1-9]|1[0-2])-(?:0[1-9]|1[0-9]|2[0-9])|(?:(?!02)(?:0[1-9]|1[0-2])-(?:30))|(?:(?:0[13578]|1[02])-31))" name="fecha" value="<?php echo $fecha ?>"/>
            Concepto: <input type="text" name="concepto" value="<?php echo $concepto ?>"/>
            Cantidad: <input type="text" name="cantidad" value="<?php echo $cantidad ?>"/>
            <input type="submit" name="accion" value="<?php echo $boton; ?>">
    </fieldset>
<?php
}

/**
 * Función de ingreso o pago.
 * 
 * @param type $user usuario activo para saber quien realiza dicho ingreso
 */
function ingreso_pago($user) {
    
    /* Volcamos en variables los datos obtenidos por el formulario */
    $fecha = $_POST['fecha'];
    $concepto = $_POST['concepto'];
    $cantidad = $_POST['cantidad'];
    
    /* Para controlar el boton de pago o ingreso */
    if (($_POST['accion']) == 'Ingresar') {
        $boton = 'Ingreso';
    } else if (($_POST['accion']) == 'Pagar') {
        $boton = 'Pagar';
    }
    
    /* Validamos los datos obtenidos */
    $flag = validacion($fecha, $concepto, $cantidad);
    
    if ($flag) { //En el caso de que ebotenga errores
        echo $flag; //Mostrará los valores de retorno de la funcion con los mensajes de validación
        formulario($boton, $fecha, $concepto, $cantidad); //Mostrará el formulario nuevamente
    } else { //Si no existen errores...
        if ($boton == 'Pagar') { //Si se trata de un pago...
            $cantidad = -$cantidad; //El valor a ingresar se negativiza
        }

        try { //Preparamos la consulta
            $codigoMov = numero_movimiento(); //Obtenemos el numero del movimiento que va a poseer invocando al formulario correspondiente
            
            $consulta = "INSERT INTO MOVIMIENTOS (codigoMov, loginUsu, fecha, concepto, cantidad) VALUES (:codigoMov, :login, :fecha, :concepto, :cantidad)";
            
            $resultado = $GLOBALS['con']->prepare($consulta);
            $resultado->bindParam(':codigoMov', $codigoMov);
            $resultado->bindParam(':login', $user);
            $resultado->bindParam(':fecha', $fecha);
            $resultado->bindParam(':concepto', $concepto);
            $resultado->bindParam(':cantidad', $cantidad);
            
            $resultado->execute(); //Ejecutamos la consulta
            
        } catch (Exception $e) { //En caso de errores
            echo "<div class='errcon'><p>Se ha producido error " . $e->getMessage() . "</p></div>"; //Capturamos el error y mostramos el mensaje
        }

        echo "<p class='perfect'>Ha realizado usted un ingreso correctamente</p>"; //Feedback satisfactorio
        
        movimientos($user); //Mostramos el listado de movimientos
    }
}


/**
 * Función que obtiene el numero del ultimo movimiento y genera el siguiente numero a modo
 * de autonumérico
 * 
 * @return Valor String de cuatro cifras 0000
 */
function numero_movimiento() {
    
    try { //Preparamos la consulta, obtiene el mayor valor real de la tabla mocimiento de codigoMov como un numero
        $consulta = "SELECT MAX(convert(codigoMov,unsigned)) AS codigo FROM movimientos";
        $resultado = $GLOBALS['con']->prepare($consulta);
        $resultado->execute();

        $registro = $resultado->fetch(PDO::FETCH_ASSOC);
        
        //var_dump($registro); //(uso de control)
        
        if ($registro['codigo'] == "") { //Si no existen registros
            $codigoMov = "0000"; //Asigna el valor inicial
        } else { //EN cualquier otor caso
            $codigoMov = $registro['codigo']; //Asignamos el valor a la variable codigoMov
            $codigoMov++; //Le añadimos una posicion más
            $codigoMov = str_pad($codigoMov, 4, '0', \STR_PAD_LEFT); //Rellenamos de ceros por la izquierda
        }
        
        //var_dump($codigoMov); //(para uso de control)

    } catch (PDOException $e) { //Si existen errores
        echo "<div class='errcon'><p>Se ha producido error " . $e->getMessage() . "</p></div>"; //Captura el error y lo muestra como mensaje
    }
    return $codigoMov; //Devuelve el codigo de movimiento siguiente
}


/**
 * Funcion movimientos, que mostrará los movimientos de la cuenta del usuario pasado por parametro
 * 
 * @param type $user usuario activo por parametro
 */
function movimientos($user){
    
    try { //Se prepara la consulta
        $consulta = "SELECT fecha, concepto, cantidad FROM movimientos WHERE loginUsu = :user";
        $resultado = $GLOBALS['con']->prepare($consulta);
        $resultado->bindParam(':user', $user);
        $resultado->execute();

        $lista = $resultado->fetchAll(); //Se vuelcan los resultados en un array listado
    } catch (PDOException $e) {//En caso de errores
        echo "<div class='errcon'><p>Se ha producido error " . $e->getMessage() . "</p></div>"; //Se captura el error y se lanza mensaje
    }
    
    //var_dump($registros); //(para uso de control)
    
    /* Conformamos la tabla en la que se mostrarán los resultados. El resto es reutilizado del ejercicio anterior*/
    echo "<h4 class='centrado'>Movimientos de su cuenta</h4>";
    
    echo "<table>";
    echo "<tr class='encabezado'><th>Fecha</th><th>Concepto</th><th>Cantidad</th><th>Saldo contable</th></tr>";
    
    if (!empty ($lista)) { //Si la lista de movimientos no esta vacia....

        $saldo = 0; //Definimos la variable del saldo
        $saldo_contable = 0; //Definimos la variable del saldo contable
        $ultimo_movimiento = (count($lista)-10); //Marcamos que deseamos ver los 10 ultimos movimientos del tamaño del array
        
        foreach ($lista as $indice => $movimiento) { //Por cada elemento del array de registros de movimientos...
            
            $saldo_contable = saldo($saldo, $movimiento); //Llamada a la funcion saldo, que caldculará el saldo con respecto a los movimientos anteriores, pese a que no sean visibles
            $saldocontable_final = number_format($saldo_contable, 2, ',', '.'); //Saldo final de la cuenta, en formato número y dos decimales
            
            if ($indice >= $ultimo_movimiento) { //Si el indice del elemento está dentro del intervalo, se muestra por filas...
                
                echo "<tr><td class='centrado'>" . $movimiento['fecha'] . "</td><td>" . $movimiento['concepto'] . "</td>"; //Muestra fecha y concepto
                
                if ($movimiento['cantidad'] > 0) { //Si la cantidad es mayor a 0
                    echo "<td class='contable'>" . number_format($movimiento['cantidad'], 2, ',', '.') . " €</td>"; //Muestra el valor normal
                } else {
                    echo "<td class='negativo'>" . number_format($movimiento['cantidad'], 2, ',', '.') . " €</td>"; //Muestra el valor en rojo (cambia css)
                }
                
                if ($saldocontable_final > 0) { //Si el saldo contable es mayor que 0
                    echo "<td class='contable'>" . $saldocontable_final . " €</td></tr>"; //Muestra el valor normal
                } else {
                    echo "<td class='negativo'>" . $saldocontable_final . " €</td></tr>"; //Muestra el valor en rojo (cambia css)
                }    
            }
            
            $saldo += $movimiento['cantidad']; //Variable donde va almacenado el saldo final
            $saldo_final = number_format($saldo, 2, ',', '.'); //Lo formateamos el saldo final total en formato redondeado a dos decimas
        }
        
        if ($saldo > 0){ //Si el saldo final es mayor que 0...
            echo "<tr class='saldoFinal'><td colspan='3'>Saldo total: </td><td>" . $saldo_final . " €</td></tr>"; //Muestra el valor normal
        } else {
            echo "<tr class='saldoFinal'><td colspan='3' >Saldo total: </td><td class='negativo'>" . $saldo_final . " €</td></tr>"; //Muestra el valor en rojo (cambia css)
        }

    } else { //En el caso de que no existan recibos en el array de movimientos... 
        echo "<tr class='centrado'><td colspan='4'>No existen recibos que visualizar</td></tr>"; //Muestra mensaje de información
    }
    echo "</table>"; //Cerramos la tabla abierta
}

/**
 * Funcion que muestra los recibos activos del usuario activo pasado por parametro
 * 
 * @param type $user usuario activo por parametro
 */
function recibos($user){
    
    try { //preparamos la consulta
        $consulta = "SELECT codigoMov, fecha, concepto, cantidad FROM movimientos WHERE loginUsu = :user";
        $resultado = $GLOBALS['con']->prepare($consulta);
        $resultado->bindParam(':user', $user);
        $resultado->execute();

        $lista = $resultado->fetchAll(); //Volcamos los resultados a un array lista
    } catch (PDOException $e) { //En caso de error
        echo "<div class='errcon'><p>Se ha producido error " . $e->getMessage() . "</p></div>"; //Capturamos el error y lanzamos mensaje
    }

    $existe_flag = false; //Creamos un flag de control para la existencia de recibos
    
    echo "<h4 class='centrado'>Recibos bancarios</h4>";
    
    //Mostramos la cabecera de la tabla
    echo "<table>";
    echo "<tr class='encabezado'><th>#</th><th>Fecha</th><th>Concepto</th><th>Cantidad</th></tr>";
    
    if (!empty ($lista)) { //Si la lista de movimientos no esta vacia....
       
        foreach ($lista as $movimiento) { //Por cada movimiento de la lista, con su indice...
            if (($movimiento['cantidad']) < 0) { //Si el importe es menor que 0, mostramos las filas, con indice (será un radio button que toma su valor), fecha, cencepto e cantidad (en rojo por css)
                echo "<tr>";
                echo "<td class='centrado'><input type='radio' name='indice' value='" . $movimiento['codigoMov'] . "'></td><td>" . $movimiento['fecha'] . "</td><td>" . $movimiento['concepto'] . "</td><td class='negativo'>" . $movimiento['cantidad'] . " €</td>";
                echo "</tr>";
                $existe_flag = true; //Al existir un recibo, marcamos el flag como true
            }
        }
        
        if ($existe_flag) { //Si existen recibos, mostramos los botones de devolver y cancelar debajo de la tabla de movimientos
            echo "</table>"; //Cerramos la tabla de movimientos
            echo "<div class='centrado'><input type='submit' name='accion' value='Devolver'> <input type='submit' name='accion' value='Cancelar'></div>"; //Creamos los botones de accion Devolver y Cancelar
        } else if (($existe_flag === false) AND (!empty($lista))) { //Si no existieran recibos y la lista tuviera aun asi movimientos...
            echo "<tr class='centrado'><td colspan='4'>No existen recibos que visualizar</td></tr></table>"; //Mostramos mensaje de feedback...
        }
        
    } else { //En el caso de no existir elementos de movimiento alguno en la cuenta
        echo "<tr class='centrado'><td colspan='4'>No existen recibos que visualizar</td></tr></table>"; //Mostramos mensaje de feedback..
    }
}


/**
 * Funcion devolver. Recibe por parametro el usuario activo y del formulario enviado el indice del movimiento, que será el codigo de movimiento
 * 
 * @param type $user
 */
function devolver($user) { //Se pasa por referencia el valor
    if ((isset($_POST['indice'])) AND ($_POST['indice']) != NULL) { //Si existe indice y este no es nulo....
        $codigoMov = $_POST['indice']; //Obtenemos el valor del código del pago
        
        try { //Preparamos la consulta
            $consulta = "DELETE FROM MOVIMIENTOS WHERE loginUsu = :user AND codigoMov = :codigoMov";
            $resultado = $GLOBALS['con']->prepare($consulta);
            $resultado->bindParam(':user', $user);
            $resultado->bindParam(':codigoMov', $codigoMov);
            $resultado->execute();

        } catch (PDOException $e) { //En caso de errores
            echo "<div class='errcon'><p>Se ha producido error " . $e->getMessage() . "</p></div>"; //Capturamos el error y lanzamos un mensaje
        }
        
        echo "<p class='perfect'><strong>INFO:</strong> Ha realizado usted una devolución satisfactoria</p>"; //Mensaje de feedback
    } else {
        echo "<p class='error'><strong>INFO:</strong> No ha seleccionado ningún pago para devolver</p>"; //Mensaje en el caso de no haber seleccionado ningun elemento de indice y haber pulsado el boton de Devolver
    }
    
    movimientos($user); //mostramos nuevamente la lista de movimientos
}

/* FUNCIONES DE COMPROBACION Y VERIFICACION */

/**
 * Funcion para comprobar que el campo login no se encuentra vacío devuelve un booleano con 
 * el resutlado de la comprobacion
 * 
 * @param type $login login introducido
 * @return boolean
 */
function comprueba_login($login) {
    if (empty($login)) {
        return false;
    }
    return true;
}

/**
 * Funcion para comprobar si el login se encuentra duplicado
 * 
 * @param type $login
 * @return boolean
 */
function comprueba_duplicado($login) {
    
    try { //Preparamos la consulta
        $consulta = "SELECT * FROM usuarios WHERE login = :login";

        $resultado = $GLOBALS['con']->prepare($consulta);
        $resultado->bindParam(":login", $login);
        $resultado->execute();

        if ($resultado->rowCount() > 0) { //Si existe ya un user con ese nombre
            return false;
        }
        return true;

    } catch (PDOException $e) { //En caso de errores
        echo "<div class='errcon'><p>Se ha producido error " . $e->getMessage() . "</p></div>"; //Capturamos el error y lanzamos un mensaje
    }
}

/**
 * Funcion que comprueba si la password esta vacia
 * 
 * @param type $pass parametro de clave
 * @return boolean 
 */
function comprueba_pass_vacia($pass) {
    if (empty($pass)) {
        return false;
    }
    return true;
}

/**
 * Funcion que comprueba si las dos claves coinciden
 * 
 * @param type $pass
 * @param type $pass2
 * @return boolean
 */
function comprueba_pass_duplicada ($pass, $pass2) {
    if ($pass != $pass2) {
        return false;
    }
    return true;
}

/**
 * Funcion que comprueba si el nombre no esta vacio
 * 
 * @param type $nombre
 * @return boolean
 */
function comprueba_nombre($nombre) {
    if (empty($nombre)) {
        return false;
    }
    return true;
}

/**
 * Funcion que comprueba si la fecha de nacimiento no esta vacia
 * 
 * @param type $fNac
 * @return boolean
 */
function comprueba_fNac($fNac) {
    if (empty($fNac)) {
        return false;
    }
    return true;
}

/**
 * Funcion que comprueba la longitud maxima del login de usuario
 * 
 * @param type $login
 * @return boolean
 */
function longitud_login($login) {
    if (strlen($login) > 10) {
        return false;
    }
    return true;
}

/**
 * Funcion que comprueba la longitud maxima del password
 * 
 * @param type $pass
 * @return boolean
 */
function longitud_pass($pass) {
    if (strlen($pass) > 20) {
        return false;
    }
    return true;
}

/**
 * Funcion que comprueba la longitud del nombre de usuario
 * 
 * @param type $nombre
 * @return boolean
 */
function longitud_nombre($nombre) {
    if (strlen($nombre) > 30) {
        return false;
    }
    return true;
}

/**
 * Funcion global que concentra todas las mini funciones de comprobacion para poder asi
 * lanzar un mensaje con los errores obtenidos a la hora de realizar validaciones.
 * 
 * Se le pasan los parametros de login en este caso dado que es para validar un usuario nuevo
 * por lo que hay que validar si ya existe un usuario en la BD.
 * 
 * @param type $login
 * @param type $pass
 * @param type $pass2
 * @param type $nombre
 * @param type $fNac
 * 
 * @return string
 */
function validar_usuario($login, $pass, $pass2, $nombre, $fNac) {
    $error = "";
    
    if (!comprueba_login($login)) {
        $error = $error . "<p class='error'><strong>ERROR: </strong>El campo login no puede estar vacio</p>";
    }
    
    if (!comprueba_duplicado($login)) {
        $error = $error . "<p class='error'><strong>ERROR: </strong>El usuario " . $login . " ya esxiste.</p>";
    }
    
    if (!longitud_login($login)) {
        $error = $error . "<p class='error'><strong>ERROR: </strong>El campo Login no puede superar los 10 caracteres</p>";
    }
    
    if (!comprueba_pass_vacia($pass)) {
        $error = $error . "<p class='error'><strong>ERROR: </strong>El campo password no puede estar vacio</p>";
    }
    
    if (!comprueba_pass_duplicada($pass, $pass2)) {
        $error = $error . "<p class='error'><strong>ERROR: </strong>El password no coincide</p>";
    }
    
    if (!longitud_pass($pass)) {
        $error = $error . "<p class='error'><strong>ERROR: </strong>El campo Password no puede superar los 20 caracteres</p>";
    }
    
    if (!comprueba_nombre($nombre)) {
        $error = $error . "<p class='error'><strong>ERROR: </strong>El campo nombre no puede estar vacio</p>";
    }
    
    if (!longitud_nombre($nombre)) {
        $error = $error . "<p class='error'><strong>ERROR: </strong>El campo Nombre no puede superar los 30 caracteres</p>";
    }
    
    if (!comprueba_fNac($fNac)) {
        $error = $error . "<p class='error'><strong>ERROR: </strong>El campo Fecha Nacimiento no puede estar vacio</p>";
    }

    return $error;
}

/**
 * Funcion global que concentra todas las mini funciones de comprobacion para poder asi
 * lanzar un mensaje con los errores obtenidos a la hora de realizar validaciones.
 * 
 * No se le pasan los parametros de login en este caso dado que es para modificar un usuario
 * ya existente, por lo que se conoce que es unico en la BD y no seria necesario validarlo.
 * 
 * @param type $pass
 * @param type $pass2
 * @param type $nombre
 * @param type $fNac
 * 
 * @return string
 */
function validar_datos($pass, $pass2, $nombre, $fNac) {
    $error = "";
    if (!comprueba_pass_vacia($pass)) {
        $error = $error . "<p class='error'><strong>ERROR: </strong>El campo password no puede estar vacio</p>";
    }
    
    if (!comprueba_pass_duplicada($pass, $pass2)) {
        $error = $error . "<p class='error'><strong>ERROR: </strong>El password no coincide</p>";
    }
    
    if (!longitud_pass($pass)) {
        $error = $error . "<p class='error'><strong>ERROR: </strong>El campo Password no puede superar los 20 caracteres</p>";
    }
    
    if (!comprueba_nombre($nombre)) {
        $error = $error . "<p class='error'><strong>ERROR: </strong>El campo nombre no puede estar vacio</p>";
    }
    
    if (!longitud_nombre($nombre)) {
        $error = $error . "<p class='error'><strong>ERROR: </strong>El campo Nombre no puede superar los 30 caracteres</p>";
    }
    
    if (!comprueba_fNac($fNac)) {
        $error = $error . "<p class='error'><strong>ERROR: </strong>El campo Fecha Nacimiento no puede estar vacio</p>";
    }
    
    return $error;
}

/**
 * Funcion independiente que valida una fecha en el formato especificado o en cualquiera que 
 * le espeficiquemos.
 * 
 * @param type $fecha fecha a pasar
 * @param type $formato formato preestablecido, modificable p.e: 'd-m-Y'
 * @return type retorna la fecha si es correcta, false si es incorrecta
 */
function validarFecha($fecha, $formato = 'Y-m-d') { //Pasamos la fecha y un valor por defecto
    $d = DateTime::createFromFormat($formato, $fecha); //Reformateamos usando el formato (modificable si queremos)
    return $d && $d->format($formato) == $fecha; //Devolvemos la fecha si es correcto, false si es incorrecto
}

/**
 * Funcion independiente que valida el concepto
 * 
 * @param type $concepto //Concepto a pasar
 * @return boolean //devuelve true o false del resultado validado
 */
function validarConcepto ($concepto) {
    if (empty($concepto)) { //Si el campo esta vacio...
        return false; //Devuelve false (no validado)
    }
    return true; //En cualquier otro caso devuelve verdadero (validado)
}

/**
 * Función independiente que valida el importe
 * 
 * @param type $importe importe a validar
 * @return boolean devuelve true o false dependiendo si esta validado o no
 */
function validarImporte ($importe) {
    if (empty($importe) OR (!is_numeric($importe)) OR ($importe < 0)) { //Si el importe esta vacío, no es numerico o es menor de cero
        return false; //Devuelve un valor false (no validado)
    }
    return true; //En cualquier otro caso, devuelve true (validado)
}


/**
 * Función que valida los tres campos, devolviendo mensaje en el caso de error, true en el caso de estar validado
 * 
 * @param type $fecha elemento fecha
 * @param type $concepto elemento cencepto
 * @param type $importe elemento importe
 *
 * @return boolean devuelve false si no llega a validar, añadiendose los mensajes de los elementos no validados
 */
function validacion ($fecha, $concepto, $importe) {
    $error = ""; //Creamos el flag del mensaje
    if (!validarFecha($fecha)) { //Si no valida la fecha, inserta el mensaje
        $error = $error . "<p class='error'><strong>ERROR:</strong> La fecha es INCORRECTA. Use el formato dd/mm/yyyy</p>";
    }
    if (!validarConcepto($concepto)) { //Si no valida el concepto, inserta el mensaje
        $error = $error . "<p class='error'><strong>ERROR:</strong> El concepto no puede estar vacío</p>";
    }
    if (!validarImporte($importe)) { //Si no valida el importe, inserta el mensaje
        $error = $error . "<p class='error'><strong>ERROR:</strong> El importe es erroneo. Ingrese un importe de forma númerica, sin simbolos. Para decimales, use punto en vez de coma</p>";
    }
    if ((validarFecha($fecha)) AND (validarConcepto($concepto)) AND (validarImporte($importe))) { //Si esta todo correcto, cambia el valor al booleano false
        $error = false;
    }
    return $error; //Devuelve el valor obtenido
}

/**
 * Función externa para el calculo del saldo contable. Mostrará el saldo que
 * hubo en cada movimiento
 * 
 * @param type $saldo Se le pasa el saldo actual en dicho momento
 * @param type $movimiento Se le pasa el movimiento que le vamos a sumar
 * @return type devolvemos el saldo sumados
 */
function saldo($saldo, $movimiento) {
    $saldo +=$movimiento['cantidad']; //Autosumatorio del movimiento
    return $saldo; //Devolvemos el saldo actualizado
}

