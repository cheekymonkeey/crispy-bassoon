from collections import defaultdict, deque


def read_input(file_path):
    with open(file_path, 'r') as file:
        lines = file.readlines()

    # Разбиение первой строки на вершины
    edges = lines[0].split()
    # Создание матрицы смежности из оставшихся строк
    matrix = [list(map(int, line.split())) for line in lines[1:]]

    return edges, matrix


def insertion_sort(arr):
    # Функция сортировки вставками для списка рёбер
    for i in range(1, len(arr)):
        key = arr[i]
        j = i - 1
        while j >= 0 and key[2] < arr[j][2]:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key


def kruskal_algorithm(edges, matrix):
    # Алгоритм Краскала для поиска минимального остова
    result = []
    vertices = len(matrix)

    # Формирование списка всех рёбер с их весами
    all_edges = [(edges[i], edges[j], matrix[i][j]) for i in range(vertices) for j in range(vertices) if
                 matrix[i][j] != 0]

    # Сортировка рёбер по весу с использованием сортировки вставками
    insertion_sort(all_edges)

    # Инициализация структур данных для работы с системой непересекающихся множеств
    parent = {edge: edge for edge in edges}
    rank = {edge: 0 for edge in edges}

    def find_parent(edge):
        # Рекурсивная функция поиска корня множества
        if parent[edge] == edge:
            return edge
        return find_parent(parent[edge])

    def union(x, y):
        # Функция объединения множеств
        x_root = find_parent(x)
        y_root = find_parent(y)

        if rank[x_root] < rank[y_root]:
            parent[x_root] = y_root
        elif rank[x_root] > rank[y_root]:
            parent[y_root] = x_root
        else:
            parent[y_root] = x_root
            rank[x_root] += 1

    for u, v, w in all_edges:
        # Проверка на цикл в графе при добавлении ребра
        if find_parent(u) != find_parent(v):
            result.append((u, v, w))
            union(u, v)

    return result


def main():
    file_path = "input.txt"
    edges, matrix = read_input(file_path)

    result = kruskal_algorithm(edges, matrix)

    insertion_sort(result)

    # Расчет общего веса
    total_weight = sum(w for _, _, w in result)

    for u, v, _ in result:
        print(f"{u} {v}")

    print(total_weight)


if __name__ == "__main__":
    main()