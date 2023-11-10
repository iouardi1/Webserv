<?php

if (isset($_COOKIE["username"])) {
    // retrieve cookie
    $username = $_COOKIE["username"];
    $login = $_COOKIE["login"];
    
    // output cookie value
    echo "Hello $username!";
    echo "\n";
    echo "Hello $login!";
  } else {
    echo "Cookie not set!";
  }

// print_r($_COOKIE);

?>
