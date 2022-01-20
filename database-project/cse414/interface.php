

<!DOCTYPE html>
<html>
<head>
<style>
table, th, td {
    border: 1px solid black;
}
</style>
</head>
<body>
<?php
    include 'config.php';
    
    $sql = "SELECT * FROM user"; //You don't need a ; like you do in SQL
    $result = $conn->query($sql);
    echo "<p><font color=#00008B font face='arial' size='4pt'>USER INTERFACE</font> <br>  </p>";
    echo "<table><tr><th>id</th><th>e-mail</th><th>phone</th><th>password</th></tr>";
   
    while($row = $result->fetch_assoc()) {
        
        echo "<tr><td>". $row["Member_id"] . "</td><td>" .'<a href="profiles.php?id='. $row["Member_id"]. '">'. $row["e_mail"] . '</a>' . 
             "</td><td>" . $row["phone"] . "</td><td>" . $row["password"] . "</td></tr>";  
       
    }
    echo "</table>";
?>
	
	

</body>
</html>