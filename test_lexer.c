/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 00:00:00 by test              #+#    #+#             */
/*   Updated: 2025/12/01 14:42:26 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <string.h>

// カラー定義
#define COLOR_GREEN "\033[0;32m"
#define COLOR_RED "\033[0;31m"
#define COLOR_YELLOW "\033[0;33m"
#define COLOR_BLUE "\033[0;34m"
#define COLOR_RESET "\033[0m"

static int			g_test_passed = 0;
static int			g_test_failed = 0;

// テスト用の期待結果構造体
typedef struct s_expected_token
{
	t_token_type	type;
	char			*str;
}					t_expected_token;

// トークン型を文字列に変換
const char	*token_type_to_string(t_token_type type)
{
	if (type == T_WORD)
		return ("T_WORD");
	else if (type == T_REDIR_IN)
		return ("T_REDIR_IN");
	else if (type == T_HEREDOC)
		return ("T_HEREDOC");
	else if (type == T_REDIR_OUT)
		return ("T_REDIR_OUT");
	else if (type == T_APPEND)
		return ("T_APPEND");
	else if (type == T_PIPE)
		return ("T_PIPE");
	else if (type == T_END)
		return ("T_END");
	else if (type == T_INVALID)
		return ("T_INVALID");
	else
		return ("UNKNOWN");
}

// トークン数をカウント
int	count_tokens(t_token *token)
{
	int		count;
	t_token	*current;

	count = 0;
	current = token;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
}

// トークンが期待値と一致するかチェック（連結リスト版）
int	check_tokens(t_token *actual, t_expected_token *expected,
		int expected_count)
{
	int		i;
	int		actual_count;
	t_token	*current;

	actual_count = count_tokens(actual);
	if (actual_count != expected_count)
	{
		printf("  " COLOR_RED "✗ Token count mismatch: expected=%d, "
				"actual=%d" COLOR_RESET "\n",
				expected_count,
				actual_count);
		return (0);
	}
	current = actual;
	i = 0;
	while (i < expected_count && current != NULL)
	{
		if (current->type != expected[i].type)
		{
			printf("  " COLOR_RED "✗ Token[%d] type mismatch: expected=%s, "
					"actual=%s" COLOR_RESET "\n",
					i,
					token_type_to_string(expected[i].type),
					token_type_to_string(current->type));
			return (0);
		}
		if (strcmp(current->str, expected[i].str) != 0)
		{
			printf("  " COLOR_RED "✗ Token[%d] str mismatch: expected=\"%s\", "
					"actual=\"%s\"" COLOR_RESET "\n",
					i,
					expected[i].str,
					current->str);
			return (0);
		}
		current = current->next;
		i++;
	}
	return (1);
}

// テスト実行
void	run_test(const char *test_id, const char *test_name, const char *input,
		t_expected_token *expected, int expected_count, t_data *data)
{
	printf("\n" COLOR_BLUE "[%s] %s" COLOR_RESET "\n", test_id, test_name);
	printf("  Input: \"%s\"\n", input);
	// データをクリア
	data->line = (char *)input;
	data->token = NULL;
	// lexer を実行
	lexer(data);
	if (data->token == NULL)
	{
		printf("  " COLOR_RED "✗ FAILED: lexer returned NULL" COLOR_RESET "\n");
		g_test_failed++;
		return ;
	}
	// 結果を表示
	print_tokens(data->token);
	// 期待値と比較
	if (check_tokens(data->token, expected, expected_count))
	{
		printf("  " COLOR_GREEN "✓ PASSED" COLOR_RESET "\n");
		g_test_passed++;
	}
	else
	{
		printf("  " COLOR_RED "✗ FAILED" COLOR_RESET "\n");
		g_test_failed++;
	}
	// トークンをクリア
	free_token_list(data->token);
	data->token = NULL;
}

// テスト環境変数を作成
char	**create_test_envp(void)
{
	char	**envp;

	envp = (char **)xmalloc(sizeof(char *) * 4);
	envp[0] = ft_strdup("USER=testuser");
	envp[1] = ft_strdup("HOME=/home/testuser");
	envp[2] = ft_strdup("PATH=/bin:/usr/bin");
	envp[3] = NULL;
	return (envp);
}

// 環境変数を解放
void	free_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		safe_free((void **)&envp[i]);
		i++;
	}
	safe_free((void **)&envp);
}

int	main(void)
{
	t_data	data;

	// データを初期化
	data.envp = create_test_envp();
	data.last_status = 0;
	data.cmd = NULL;
	data.cur_cmd = NULL;
	data.token = NULL;
	data.line = NULL;
	printf("\n");
	printf("========================================\n");
	printf("  Lexer Test Suite (33 Test Cases)\n");
	printf("========================================\n");
	// ============================================================
	// カテゴリ 1: 基本的なコマンド
	// ============================================================
	// Test 1-1: シンプルなコマンド
	{
		t_expected_token expected[] = {{T_WORD, "echo"}, {T_WORD, "hello"}};
		run_test("1-1", "シンプルなコマンド", "echo hello", expected, 2, &data);
	}
	// Test 1-2: 複数引数
	{
		t_expected_token expected[] = {{T_WORD, "ls"}, {T_WORD, "-la"}, {T_WORD, "/home"}};
		run_test("1-2", "複数引数", "ls -la /home", expected, 3, &data);
	}
	// Test 1-3: 余分な空白
	{
		t_expected_token expected[] = {{T_WORD, "echo"}, {T_WORD, "hello"}, {T_WORD, "world"}};
		run_test("1-3", "余分な空白", "echo    hello     world", expected, 3, &data);
	}
	// ============================================================
	// カテゴリ 2: リダイレクション
	// ============================================================
	// Test 2-1: 入力リダイレクト (<)
	{
		t_expected_token expected[] = {{T_WORD, "cat"}, {T_REDIR_IN, "<"}, {T_WORD, "input.txt"}};
		run_test("2-1", "入力リダイレクト (<)", "cat < input.txt", expected, 3, &data);
	}
	// Test 2-2: 出力リダイレクト (>)
	{
		t_expected_token expected[] = {{T_WORD, "echo"}, {T_WORD, "hello"}, {T_REDIR_OUT, ">"}, {T_WORD, "output.txt"}};
		run_test("2-2", "出力リダイレクト (>)", "echo hello > output.txt", expected, 4,
			&data);
	}
	// Test 2-3: 追記リダイレクト (>>)
	{
		t_expected_token expected[] = {{T_WORD, "echo"}, {T_WORD, "hello"}, {T_APPEND, ">>"}, {T_WORD, "output.txt"}};
		run_test("2-3", "追記リダイレクト (>>)", "echo hello >> output.txt", expected,
			4, &data);
	}
	// Test 2-4: Here Document (<<)
	{
		t_expected_token expected[] = {{T_WORD, "cat"}, {T_HEREDOC, "<<"}, {T_WORD, "EOF"}};
		run_test("2-4", "Here Document (<<)", "cat << EOF", expected, 3, &data);
	}
	// Test 2-5: 複数リダイレクト
	{
		t_expected_token expected[] = {{T_WORD, "cat"}, {T_REDIR_IN, "<"}, {T_WORD, "in.txt"}, {T_REDIR_OUT, ">"}, {T_WORD, "out.txt"}};
		run_test("2-5", "複数リダイレクト", "cat < in.txt > out.txt", expected, 5,
			&data);
	}
	// Test 2-6: スペースなしリダイレクト
	{
		t_expected_token expected[] = {{T_WORD, "cat"}, {T_REDIR_IN, "<"}, {T_WORD, "input.txt"}, {T_REDIR_OUT, ">"}, {T_WORD, "output.txt"}};
		run_test("2-6", "スペースなしリダイレクト", "cat<input.txt>output.txt", expected, 5,
			&data);
	}
	// ============================================================
	// カテゴリ 3: パイプ
	// ============================================================
	// Test 3-1: シンプルなパイプ
	{
		t_expected_token expected[] = {{T_WORD, "ls"}, {T_PIPE, "|"}, {T_WORD, "grep"}, {T_WORD, "txt"}};
		run_test("3-1", "シンプルなパイプ", "ls | grep txt", expected, 4, &data);
	}
	// Test 3-2: 複数パイプ
	{
		t_expected_token expected[] = {{T_WORD, "cat"}, {T_WORD, "file.txt"}, {T_PIPE, "|"}, {T_WORD, "grep"}, {T_WORD, "error"}, {T_PIPE, "|"}, {T_WORD, "wc"}, {T_WORD, "-l"}};
		run_test("3-2", "複数パイプ", "cat file.txt | grep error | wc -l", expected,
			8, &data);
	}
	// Test 3-3: パイプとリダイレクションの組み合わせ
	{
		t_expected_token expected[] = {{T_WORD, "cat"}, {T_REDIR_IN, "<"}, {T_WORD, "input.txt"}, {T_PIPE, "|"}, {T_WORD, "grep"}, {T_WORD, "hello"}, {T_REDIR_OUT, ">"}, {T_WORD, "output.txt"}};
		run_test("3-3", "パイプとリダイレクションの組み合わせ",
			"cat < input.txt | grep hello > output.txt", expected, 8, &data);
	}
	// ============================================================
	// カテゴリ 4: 引用符処理
	// ============================================================
	// Test 4-1: シングルクォート
	{
		t_expected_token expected[] = {{T_WORD, "echo"}, {T_WORD, "hello world"}};
		run_test("4-1", "シングルクォート", "echo 'hello world'", expected, 2, &data);
	}
	// Test 4-2: ダブルクォート
	{
		t_expected_token expected[] = {{T_WORD, "echo"}, {T_WORD, "hello world"}};
		run_test("4-2", "ダブルクォート", "echo \"hello world\"", expected, 2, &data);
	}
	// Test 4-3: 空のクォート
	{
		t_expected_token expected[] = {{T_WORD, "echo"}, {T_WORD, ""}};
		run_test("4-3", "空のクォート", "echo ''", expected, 2, &data);
	}
	// Test 4-4: クォート内のスペース
	{
		t_expected_token expected[] = {{T_WORD, "echo"}, {T_WORD, "   hello   "}};
		run_test("4-4", "クォート内のスペース", "echo '   hello   '", expected, 2, &data);
	}
	// Test 4-5: クォート内のメタキャラクタ
	{
		t_expected_token expected[] = {{T_WORD, "echo"}, {T_WORD, "hello | world"}};
		run_test("4-5", "クォート内のメタキャラクタ", "echo 'hello | world'", expected, 2,
			&data);
	}
	// Test 4-6: 混在するクォート
	{
		t_expected_token expected[] = {{T_WORD, "echo"}, {T_WORD, "hello"}, {T_WORD, "world"}};
		run_test("4-6", "混在するクォート", "echo 'hello' world", expected, 3, &data);
	}
	// Test 4-7: 連続するクォート（スペースなし）
	{
		t_expected_token expected[] = {{T_WORD, "echo"}, {T_WORD, "helloworld"}};
		run_test("4-7", "連続するクォート（スペースなし）", "echo 'hello'world", expected, 2,
			&data);
	}
	// ============================================================
	// カテゴリ 5: 環境変数展開
	// ============================================================
	// Test 5-1: 基本的な環境変数
	{
		t_expected_token expected[] = {{T_WORD, "echo"}, {T_WORD, "testuser"}};
		run_test("5-1", "基本的な環境変数", "echo $USER", expected, 2, &data);
	}
	// Test 5-2: ダブルクォート内の環境変数
	{
		t_expected_token expected[] = {{T_WORD, "echo"}, {T_WORD, "Hello testuser"}};
		run_test("5-2", "ダブルクォート内の環境変数", "echo \"Hello $USER\"", expected, 2,
			&data);
	}
	// Test 5-3: シングルクォート内の環境変数（展開されない）
	{
		t_expected_token expected[] = {{T_WORD, "echo"}, {T_WORD, "$USER"}};
		run_test("5-3", "シングルクォート内の環境変数（展開されない）", "echo '$USER'", expected, 2,
			&data);
	}
	// Test 5-4: 存在しない環境変数
	{
		t_expected_token expected[] = {{T_WORD, "echo"}, {T_WORD, ""}};
		run_test("5-4", "存在しない環境変数", "echo $NONEXISTENT", expected, 2, &data);
	}
	// Test 5-5: 特殊変数 $?（終了ステータス）
	{
		data.last_status = 42;
		t_expected_token expected[] = {{T_WORD, "echo"}, {T_WORD, "42"}};
		run_test("5-5", "特殊変数 $?（終了ステータス）", "echo $?", expected, 2, &data);
		data.last_status = 0;
	}
	// ============================================================
	// カテゴリ 6: エッジケース
	// ============================================================
	// Test 6-1: 空文字列
	{
		t_expected_token expected[] = {};
		run_test("6-1", "空文字列", "", expected, 0, &data);
	}
	// Test 6-2: スペースのみ
	{
		t_expected_token expected[] = {};
		run_test("6-2", "スペースのみ", "     ", expected, 0, &data);
	}
	// Test 6-3: タブのみ
	{
		t_expected_token expected[] = {};
		run_test("6-3", "タブのみ", "\t\t\t", expected, 0, &data);
	}
	// Test 6-4: 閉じられていないクォート（シングル）
	{
		t_expected_token expected[] = {{T_WORD, "echo"}, {T_WORD, "hello"}};
		run_test("6-4", "閉じられていないクォート（シングル）", "echo 'hello", expected, 2,
			&data);
	}
	// Test 6-5: 閉じられていないクォート（ダブル）
	{
		t_expected_token expected[] = {{T_WORD, "echo"}, {T_WORD, "hello"}};
		run_test("6-5", "閉じられていないクォート（ダブル）", "echo \"hello", expected, 2,
			&data);
	}
	// Test 6-6: 連続するリダイレクト
	{
		t_expected_token expected[] = {{T_WORD, "cat"}, {T_HEREDOC, "<<"}, {T_REDIR_IN, "<"}, {T_WORD, "file.txt"}};
		run_test("6-6", "連続するリダイレクト", "cat << < file.txt", expected, 4, &data);
	}
	// Test 6-7: || （無効な演算子）
	{
		t_expected_token expected[] = {{T_WORD, "echo"}, {T_WORD, "hello"}, {T_INVALID, "||"}, {T_WORD, "echo"}, {T_WORD, "world"}};
		run_test("6-7", "|| （無効な演算子）", "echo hello || echo world", expected, 5,
			&data);
	}
	// ============================================================
	// カテゴリ 7: 複雑な組み合わせ
	// ============================================================
	// Test 7-1: すべての要素の組み合わせ
	{
		t_expected_token expected[] = {{T_WORD, "cat"}, {T_REDIR_IN, "<"}, {T_WORD, "input.txt"}, {T_PIPE, "|"}, {T_WORD, "grep"}, {T_WORD, "hello world"}, {T_PIPE, "|"}, {T_WORD, "wc"}, {T_WORD, "-l"}, {T_REDIR_OUT, ">"}, {T_WORD, "output.txt"}};
		run_test("7-1", "すべての要素の組み合わせ",
			"cat < input.txt | grep 'hello world' | wc -l > output.txt",
			expected, 11, &data);
	}
	// Test 7-2: 環境変数とクォートの混在
	{
		t_expected_token expected[] = {{T_WORD, "echo"}, {T_WORD, "User: testuser"}, {T_WORD, "literal $HOME"}};
		run_test("7-2", "環境変数とクォートの混在", "echo \"User: $USER\" 'literal $HOME'",
			expected, 3, &data);
	}
	// Test 7-3: 複雑なパス
	{
		t_expected_token expected[] = {{T_WORD, "cat"}, {T_WORD, "/home/user/documents/file.txt"}};
		run_test("7-3", "複雑なパス", "cat /home/user/documents/file.txt", expected,
			2, &data);
	}
	// ============================================================
	// テスト結果の表示
	// ============================================================
	printf("\n");
	printf("========================================\n");
	printf("  Test Results\n");
	printf("========================================\n");
	printf("  " COLOR_GREEN "Passed: %d" COLOR_RESET "\n", g_test_passed);
	printf("  " COLOR_RED "Failed: %d" COLOR_RESET "\n", g_test_failed);
	printf("  Total:  %d\n", g_test_passed + g_test_failed);
	if (g_test_failed == 0)
	{
		printf("\n  " COLOR_GREEN "✓ All tests passed!" COLOR_RESET "\n");
	}
	else
	{
		printf("\n  " COLOR_RED "✗ Some tests failed." COLOR_RESET "\n");
	}
	printf("========================================\n\n");
	// クリーンアップ
	free_envp(data.envp);
	return ((g_test_failed == 0) ? 0 : 1);
}
