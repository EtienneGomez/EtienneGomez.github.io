<?php
  // Comprueba si el usuario ha enviado el formulario
  if (isset($_POST["network_address"]) && isset($_POST["netmask"]) && isset($_FILES["code_file"])) {
    // Obtén los datos del formulario
    $network_address = $_POST["network_address"];
    $netmask = $_POST["netmask"];
    $code_file = $_FILES["code_file"];

    // Compila el código C++
    $compiler = 'g++ -o calculadoraip.cpp';
    exec($compiler);

    // Ejecuta el código C++
    $process = exec('./calculator ' . $network_address . ' ' . $netmask);

    // Devuelve los resultados del cálculo
    echo $process;
  }
?>
