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
    $sql = "SELECT * FROM liked_movies"; //You don't need a ; like you do in SQL
    $movie = "SELECT * FROM movies";
    $result = $conn->query($sql);
    $result1 = $conn->query($movie);
    echo "<p><font color=#00008B font face='arial' size='4pt'>PROFILE INTERFACE</font> <br>  </p>";
    echo "<font color=#cc0000 font face='arial' size='3pt'>Liked Movies</font> <br>";
    echo "<table><tr><th>profile_id</th><th>e-movie_id</th><th>movie_name</th></tr>";
    
    
    while($row = $result->fetch_assoc()) {
        if($row["profile_id"] == $_GET['id']) {
            while($row1 = $result1->fetch_assoc()) {
                if ($row["movie_id"] == $row1["id"]) {
                    $temp = $row1["Title"] ;
                }
                
            }
            echo "<tr><td>". $row["profile_id"] . "</td><td>" . $row["movie_id"] .
                 "</td><td>" . $temp . "</td></tr>"; 
            $result1 =$conn->query($movie);
        }
    }
    echo "</table>";
    
?>
<br>
<?php
    $sql = "SELECT * FROM disliked_movies"; //You don't need a ; like you do in SQL
    $movie = "SELECT * FROM movies";
    $result = $conn->query($sql);
    $result1 = $conn->query($movie);
    echo "<font color=#cc0000 font face='arial' size='3pt'>Disiked Movies</font> <br>";
    echo "<table><tr><th>profile_id</th><th>e-movie_id</th><th>movie_name</th></tr>";
    
    
    while($row = $result->fetch_assoc()) {
        if($row["profile_id"] == $_GET['id']) {
            while($row1 = $result1->fetch_assoc()) {
                if ($row["movie_id"] == $row1["id"]) {
                    $temp = $row1["Title"] ;
                }
                
            }
            echo "<tr><td>". $row["profile_id"] . "</td><td>" . $row["movie_id"] .
            "</td><td>" . $temp . "</td></tr>";
            $result1 =$conn->query($movie);
        }
    }
    echo "</table>";
    
?>
	<br>
<?php
    $sql = "SELECT * FROM watching"; //You don't need a ; like you do in SQL
    $movie = "SELECT * FROM movies";
    $result = $conn->query($sql);
    $result1 = $conn->query($movie);
    echo "<font color=#cc0000 font face='arial' size='3pt'>Continue to Watch</font> <br>";
    echo "<table><tr><th>profile_id</th><th>movie_id</th><th>movie_name</th><th>at_time</th></tr>";
        
    
    while($row = $result->fetch_assoc()) {
        if($row["Profile_id"] == $_GET['id']){
            while($row1 = $result1->fetch_assoc()) {
                if ($row["Movie_id"] == $row1["id"]) {
                    $temp = $row1["Title"] ;
                }
                
            }
            echo "<tr><td>". $row["Profile_id"] . "</td><td>" . $row["Movie_id"] .
            "</td><td>" . $temp . "</td><td>" . $row["at_time"] . "</td></tr>";
            $result1 =$conn->query($movie);

        }
    }
    echo "</table>";

?>

<br>
<?php
    $sql = "SELECT * FROM watched"; //You don't need a ; like you do in SQL
    $movie = "SELECT * FROM movies";
    $result = $conn->query($sql);
    $result1 = $conn->query($movie);
    echo "<font color=#cc0000 font face='arial' size='3pt'>Watched Movies</font> <br>";
    echo "<table><tr><th>profile_id</th><th>e-movie_id</th><th>movie_name</th></tr>";
    
    
    while($row = $result->fetch_assoc()) {
        if($row["profile_id"] == $_GET['id']){
            while($row1 = $result1->fetch_assoc()) {
                if ($row["movie_id"] == $row1["id"]) {
                    $temp = $row1["Title"] ;
                }
                
            }
            echo "<tr><td>". $row["profile_id"] . "</td><td>" . $row["movie_id"] .
            "</td><td>" . $temp . "</td></tr>";
            $result1 =$conn->query($movie);
        }
    }
    echo "</table>";
    $conn->close();
?>
</body>
</html>