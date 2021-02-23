extends PanelContainer


onready var id_line: = $VBoxContainer/ID/LineEdit
onready var username_line: = $VBoxContainer/Username/LineEdit
onready var discriminator_line: = $VBoxContainer/Discriminator/LineEdit
onready var avatar_line: = $VBoxContainer/Avatar/LineEdit
onready var bot_line: = $VBoxContainer/Bot/LineEdit

var user: Discord.User setget set_user


func set_user(new_user: Discord.User) -> void:
	if new_user:
		id_line.text = str(new_user.id)
		username_line.text = new_user.username
		discriminator_line.text = new_user.discriminator
		avatar_line.text = new_user.avatar
		bot_line.text = str(new_user.bot)
