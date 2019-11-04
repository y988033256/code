<?php
$dbConn = new mysqli('localhost', 'unn_w15020771', '302Yhm402', 'unn_w15020771');

if ($dbConn->connect_error) {
    echo "<p>Connection failed: ".$dbConn->connect_error."</p>\n";
    exit;
}
?>