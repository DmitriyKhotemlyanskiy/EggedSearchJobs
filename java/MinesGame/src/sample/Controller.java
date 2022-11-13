package sample;

import java.io.InputStream;
import java.net.URL;
import java.util.ResourceBundle;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.geometry.Insets;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.effect.BlendMode;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.input.MouseButton;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.text.Font;

public class Controller {
    private static int newHeight = 0;
    private static int newWidth = 0;
    private static int newMines = 0;
    private int count = 0;
    private int indexOfX;
    private int indexOfY;
    private Mines play;
    @FXML
    private ResourceBundle resources;

    @FXML
    private URL location;

    @FXML
    private AnchorPane anchorMain;

    @FXML
    private HBox mainHBox;

    @FXML
    private Button resetButton;

    @FXML
    private TextField widthTField;

    @FXML
    private TextField heightTField;

    @FXML
    private TextField minesTField;

    @FXML
    private GridPane gridPaneMines;


    @FXML
    private GridPane createGridPane(Mines p){

        for (int i=0;i<newHeight;i++) {
            for(int j = 0;j<newWidth;j++) {
                Button bButton = new Button();
                Image img;
                ImageView imgView;
                if(p.get(i,j).equals(".")){
                    img = new Image("box_address.png");
                    imgView = new ImageView(img);
                    imgView.setFitHeight(40);
                    imgView.setFitWidth(40);
                    bButton.setGraphic(imgView);
                }
                else if(p.get(i,j).equals("F")) {
                    img = new Image("flag_israel.png");
                    imgView = new ImageView(img);
                    imgView.setFitHeight(40);
                    imgView.setFitWidth(40);
                    bButton.setGraphic(imgView);
                }
                else if(p.get(i,j).equals("X")) {
                    img = new Image("bomb.png");
                    imgView = new ImageView(img);
                    imgView.setFitHeight(40);
                    imgView.setFitWidth(40);
                    bButton.setGraphic(imgView);
                }
                else if(p.get(i,j).equals(" ")) {
                    img = new Image("emptyButton.png");
                    imgView = new ImageView(img);
                    imgView.setFitHeight(40);
                    imgView.setFitWidth(40);
                    imgView.setOpacity(0.4);
                    bButton.setGraphic(imgView);
                }
                else if(p.get(i,j).equals("1")) {
                    img = new Image("key_1.png");
                    imgView = new ImageView(img);
                    imgView.setFitHeight(40);
                    imgView.setFitWidth(40);
                    bButton.setGraphic(imgView);
                }
                else if(p.get(i,j).equals("2")) {
                    img = new Image("key_2.png");
                    imgView = new ImageView(img);
                    imgView.setFitHeight(40);
                    imgView.setFitWidth(40);
                    bButton.setGraphic(imgView);
                }
                else if(p.get(i,j).equals("3")) {
                    img = new Image("key_3.png");
                    imgView = new ImageView(img);
                    imgView.setFitHeight(40);
                    imgView.setFitWidth(40);
                    bButton.setGraphic(imgView);
                }
                else if(p.get(i,j).equals("4")) {
                    img = new Image("key_4.png");
                    imgView = new ImageView(img);
                    imgView.setFitHeight(40);
                    imgView.setFitWidth(40);
                    bButton.setGraphic(imgView);
                }
                else if(p.get(i,j).equals("5")) {
                    img = new Image("key_5.png");
                    imgView = new ImageView(img);
                    imgView.setFitHeight(40);
                    imgView.setFitWidth(40);
                    bButton.setGraphic(imgView);
                }
                else if(p.get(i,j).equals("6")) {
                    img = new Image("key_6.png");
                    imgView = new ImageView(img);
                    imgView.setFitHeight(40);
                    imgView.setFitWidth(40);
                    bButton.setGraphic(imgView);
                }

                bButton.addEventFilter(MouseEvent.MOUSE_CLICKED, new EventHandler<MouseEvent>() {
                    @Override
                    public void handle(MouseEvent event) {
                        if(event.getButton() == MouseButton.SECONDARY){
                            indexOfX = GridPane.getRowIndex(bButton);
                            indexOfY = GridPane.getColumnIndex(bButton);
                            play.toggleFlag(indexOfX,indexOfY);
                            play.setShowAll(false);
                            gridPaneMines.getChildren().remove(0,newWidth*newHeight);
                            if(play.isDone()){
                                new ModalWindow().WinnerWindow("WINNER!!!"); //checking if the game has ended by click on flag
                            }
                            mainHBox.getChildren().set(1,createGridPane(play));
                        }
                    }
                });
                bButton.setOnAction(MouseEvent -> thisButton(bButton));
                gridPaneMines.add(bButton,j,i);
            }
        }
        return gridPaneMines;
    }

    private void thisButton(Button thisB) {
        indexOfX = GridPane.getRowIndex(thisB);
        indexOfY = GridPane.getColumnIndex(thisB);
        play.open(indexOfX,indexOfY);
        gridPaneMines.getChildren().remove(0,newWidth*newHeight);
        if(play.get(indexOfX,indexOfY).equals("X")){
            new ModalWindow().LooserWindow("LOOSER!!!"); //checking if the game has ended by click on flag
            play.setShowAll(true);
        }
        if(play.isDone()){
            new ModalWindow().WinnerWindow("WINNER!!!");
        }
        mainHBox.getChildren().set(1,createGridPane(play));
    }

     public int itsGood(int height, int width, int mines){

         if(newWidth<0||newWidth == 0) {
             return 1;
         }
         else if (newHeight<0||newHeight ==0) {
             return 2;
         }
         else if (newMines<0||newMines==0){
             return 3;
         }
         if(newMines>=newHeight*newWidth)
             return 4;
         return 0;
     }

     public static void setNewHeight(int val){ newHeight = val;}
    public static void setNewWidth(int val){
        newWidth = val;
    }
    public static void setNewMines(int val){ newMines = val; }



    @FXML
    void initialize() {

        resetButton.setOnAction(event -> {
            if(count!=0) gridPaneMines.getChildren().remove(0,newWidth*newHeight);
            newMines = Integer.parseInt(minesTField.getText().trim());
            newWidth = Integer.parseInt(widthTField.getText().trim());
            newHeight = Integer.parseInt(heightTField.getText().trim());
            int op = itsGood(newHeight,newWidth,newMines);
            while(op != 0){
                if(op == 1){
                    new ModalWindow().ErrorWindow("WIDTH");
                    op = itsGood(newHeight,newWidth,newMines);
                }
                if(op ==2){
                    new ModalWindow().ErrorWindow("HEIGHT");
                    op=itsGood(newHeight,newWidth,newMines);
                }
                if(op==3) {
                    new ModalWindow().ErrorWindow("MINES");
                    op = itsGood(newHeight,newWidth,newMines);
                }
                if(op==4){
                    new ModalWindow().ErrorWindow("MINES");
                    op=itsGood(newHeight,newWidth,newMines);
                }

            }
            minesTField.setText(String.valueOf(newMines));
            heightTField.setText(String.valueOf(newHeight));
            widthTField.setText(String.valueOf(newWidth));
            play = new Mines(newHeight,newWidth,newMines);
            mainHBox.getChildren().set(1,createGridPane(play));
            count++;
        });
    }
}
