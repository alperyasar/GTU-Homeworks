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
    
    
    while($row = $result->fetch_assoc()) {
        if ($row["id"] == $_GET['id']) {
            echo "<p><font color=#00008B font face='arial' size='4pt'>" . $row["Title"] . "</font> <br>  </p>";
            echo "<table><tr><th>id</th><th>Title</th><th>Lenght</th><th>Rating</th><th>Views</th></tr>";
            echo "<tr><td>". $row["id"] . "</td><td>" . $row["Title"] .
            "</td><td>" . $row["Lenght"] . "</td><td>". $row["Rating"] .
            "</td><td>". $row["Views"] ."</td></tr>";
            echo "</table>";
        }
    }
?>
<br>
<?php

    $sql = "SELECT * FROM movie_stars"; //You don't need a ; like you do in SQL
    $star = "SELECT * FROM stars"; //You don't need a ; like you do in SQL
    $result = $conn->query($sql);
    $result1 = $conn->query($star);
    echo "<font color=#cc0000 font face='arial' size='3pt'>Stars</font> <br>";
    echo "<table><tr><th>id</th><th>Name</th><th>Surname</th><th>Gender</th></tr>";
    
    while($row = $result->fetch_assoc()) {
        if ($row["Movie_id"] == $_GET['id']) {
            while ($row1 = $result1->fetch_assoc()) {
                if ($row1["id"] == $row["star_id"]) {
                    echo "<tr><td>". $row1["id"] . "</td><td>" . $row1["Name"] .
                    "</td><td>" . $row1["Surname"] . "</td><td>". $row1["Gender"]  ."</td></tr>";
                }
            }
            $result1 =$conn->query($star);
        }
    }
    echo "</table>";
?>

<br>
<?php

    $sql = "SELECT * FROM movie_director"; //You don't need a ; like you do in SQL
    $director = "SELECT * FROM director"; //You don't need a ; like you do in SQL
    $result = $conn->query($sql);
    $result1 = $conn->query($director);
    echo "<font color=#cc0000 font face='arial' size='3pt'>Directors</font> <br>";
    echo "<table><tr><th>id</th><th>Name</th><th>Surname</th><th>Gender</th></tr>";
    
    while($row = $result->fetch_assoc()) {
        if ($row["Movie_id"] == $_GET['id']) {
            while ($row1 = $result1->fetch_assoc()) {
                if ($row1["id"] == $row["director_id"]) {
                    echo "<tr><td>". $row1["id"] . "</td><td>" . $row1["Name"] .
                    "</td><td>" . $row1["Surname"] . "</td><td>". $row1["Gender"]  ."</td></tr>";
                }
            }
            $result1 =$conn->query($director);
        }
    }
    echo "</table>";
?>

<br>
<?php

    $sql = "SELECT * FROM genres"; //You don't need a ; like you do in SQL
    $result = $conn->query($sql);
    echo "<font color=#cc0000 font face='arial' size='3pt'>Genres</font> <br>";
    echo "<table><tr><th>Movie_id</th><th>Name</th></tr>";


    while($row = $result->fetch_assoc()) {
        if ($row["Movie_id"] == $_GET['id']) {
            echo "<tr><td>". $row["Movie_id"] . "</td><td>" . $row["Name"]."</td></tr>";
            
        }
    }
    echo "</table>";
?>

<br>
<?php

    $sql = "SELECT * FROM awards"; //You don't need a ; like you do in SQL
    $result = $conn->query($sql);
    echo "<font color=#cc0000 font face='arial' size='3pt'>Awards</font> <br>";
    echo "<table><tr><th>Movie_id</th><th>Name</th></tr>";


    while($row = $result->fetch_assoc()) {
        if ($row["Movie_id"] == $_GET['id']) {
            echo "<tr><td>". $row["Movie_id"] . "</td><td>" . $row["Name"]."</td></tr>";
            
        }
    }
    echo "</table>";
?>

<br>
<?php

    $sql = "SELECT * FROM subtitle"; //You don't need a ; like you do in SQL
    $result = $conn->query($sql);
    echo "<font color=#cc0000 font face='arial' size='3pt'>Subtitle</font> <br>";
    echo "<table><tr><th>Movie_id</th><th>Language</th></tr>";


    while($row = $result->fetch_assoc()) {
        if ($row["Movie_id"] == $_GET['id']) {
            echo "<tr><td>". $row["Movie_id"] . "</td><td>" . $row["Language"]."</td></tr>";
            
        }
    }
    echo "</table>";
?>

<br>
<?php

    $sql = "SELECT * FROM speak"; //You don't need a ; like you do in SQL
    $result = $conn->query($sql);
    echo "<font color=#cc0000 font face='arial' size='3pt'>Speak</font> <br>";
    echo "<table><tr><th>Movie_id</th><th>Language</th></tr>";


    while($row = $result->fetch_assoc()) {
        if ($row["Movie_id"] == $_GET['id']) {
            echo "<tr><td>". $row["Movie_id"] . "</td><td>" . $row["Language"]."</td></tr>";
            
        }
    }
    echo "</table>";
?>
</body>
</html>