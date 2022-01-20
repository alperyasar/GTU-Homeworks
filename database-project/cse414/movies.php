
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
    
    $sql = "SELECT * FROM movies"; //You don't need a ; like you do in SQL
    $result = $conn->query($sql);
    echo "<p><font color=#00008B font face='arial' size='4pt'>MOVIES INTERFACE</font> <br>  </p>";
    echo "<table><tr><th>id</th><th>Title</th><th>Lenght</th><th>Rating</th><th>Views</th></tr>";

   
    while($row = $result->fetch_assoc()) {
        echo "<tr><td>". $row["id"] . "</td><td>" . '<a href="movie.php?id='. $row["id"]. '">'. $row["Title"] . '</a>'  . "</td><td>" . $row["Lenght"] . 
        "</td><td>" . $row["Rating"] ."</td><td>" . $row["Views"]  . "</td></tr>";  
 
    }
    echo "</table>";
    $conn->close();
?>

	

</body>
</html>