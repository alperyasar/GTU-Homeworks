

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
    $sql = "SELECT * FROM profile"; //You don't need a ; like you do in SQL
    $result = $conn->query($sql);
    echo "<p><font color=#00008B font face='arial' size='4pt'>USER INTERFACE</font> <br>  </p>";
    echo "<table><tr><th>id</th><th>user_id</th><th>Name</th></tr>";
   
    while($row = $result->fetch_assoc()) {
        if ($row["user_id"] == $_GET['id']) {
            echo "<tr><td>". $row["id"] . "</td><td>" . $row["user_id"]  .  "</td><td>" .
                '<a href="profile.php?id='. $row["id"]. '">'. $row["Name"] . '</a>' . "</td></tr>";
        }
          
       
    }
    echo "</table>";
    $conn->close();
?>

	
	

</body>
</html>